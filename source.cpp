#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <zlib.h>
#include <mutex>

using namespace std;

const size_t CHUNK_SIZE = 1024 * 1024; // 1 MB
mutex io_mutex;

struct Chunk {
    vector<unsigned char> input;
    vector<unsigned char> output;
    uLong sourceSize = 0;
    uLong destSize = 0;
};

void compressChunk(Chunk &chunk) {
    chunk.output.resize(compressBound(chunk.input.size()));
    chunk.sourceSize = chunk.input.size();
    compress(chunk.output.data(), &chunk.destSize, chunk.input.data(), chunk.sourceSize);
    chunk.output.resize(chunk.destSize);
}

void decompressChunk(Chunk &chunk) {
    chunk.output.resize(chunk.sourceSize);
    uncompress(chunk.output.data(), &chunk.destSize, chunk.input.data(), chunk.sourceSize);
}

void compressFile(const string &inputFile, const string &outputFile) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    if (!in || !out) {
        cout << "File error.\n";
        return;
    }

    vector<thread> threads;
    vector<Chunk> chunks;

    while (!in.eof()) {
        Chunk chunk;
        chunk.input.resize(CHUNK_SIZE);
        in.read((char *)chunk.input.data(), CHUNK_SIZE);
        size_t bytesRead = in.gcount();
        chunk.input.resize(bytesRead);
        chunk.destSize = compressBound(bytesRead);
        chunks.push_back(chunk);
    }

    for (auto &chunk : chunks)
        threads.emplace_back(compressChunk, ref(chunk));

    for (auto &t : threads)
        t.join();

    for (auto &chunk : chunks) {
        out.write((char *)&chunk.destSize, sizeof(uLong));
        out.write((char *)&chunk.sourceSize, sizeof(uLong));
        out.write((char *)chunk.output.data(), chunk.destSize);
    }

    cout << "Compression complete.\n";
}

void decompressFile(const string &inputFile, const string &outputFile) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    if (!in || !out) {
        cout << "File error.\n";
        return;
    }

    vector<thread> threads;
    vector<Chunk> chunks;

    while (!in.eof()) {
        Chunk chunk;
        uLong compSize, origSize;
        in.read((char *)&compSize, sizeof(uLong));
        in.read((char *)&origSize, sizeof(uLong));

        if (in.eof()) break;

        chunk.input.resize(compSize);
        chunk.sourceSize = compSize;
        chunk.destSize = origSize;

        in.read((char *)chunk.input.data(), compSize);
        chunks.push_back(chunk);
    }

    for (auto &chunk : chunks)
        threads.emplace_back(decompressChunk, ref(chunk));

    for (auto &t : threads)
        t.join();

    for (auto &chunk : chunks)
        out.write((char *)chunk.output.data(), chunk.destSize);

    cout << "Decompression complete.\n";
}

int main() {
    int choice;
    string inputFile, outputFile;

    do {
        cout << "\n=== FILE COMPRESSOR ===\n";
        cout << "1. Compress File\n";
        cout << "2. Decompress File\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter input file to compress: ";
                cin >> inputFile;
                cout << "Enter output compressed file: ";
                cin >> outputFile;
                compressFile(inputFile, outputFile);
                break;

            case 2:
                cout << "Enter compressed input file: ";
                cin >> inputFile;
                cout << "Enter output decompressed file: ";
                cin >> outputFile;
                decompressFile(inputFile, outputFile);
                break;

            case 3:
                cout << "Exiting.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
