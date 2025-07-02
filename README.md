
# Multithreaded File Compressor & Decompressor in C++

- **Name:** `ANUP MANDAL`  
- **Company:** `CODTECH IT SOLUTIONS`  
- **ID:** `CT04DF2235`  
- **Domain:** `C++ Programming`  
- **Internship Duration:** `June 2nd, 2025` – `July 2nd, 2025`

---

## 📄 Project Overview

This project is a **console-based multithreaded file compressor and decompressor** built using **C++**, **zlib**, and **multithreading**.  
It compresses large files by dividing them into chunks and processing each in a separate thread to increase performance.

The tool allows users to:

- Compress any input file to a smaller `.bin` format.  
- Decompress the compressed file back to its original form.

---

## 🚀 Features

- Compress any text or binary file  
- Decompress previously compressed files  
- Uses `zlib` for compression  
- Multi-threaded chunk-based processing  
- Supports large files by splitting into 1MB blocks  
- Simple text-based user interface

---

## 📂 File Structure

```

FileCompressor/
├── source.cpp
├── README.md
└── testFiles/
├── sample.txt
├── sample\_compressed.bin
└── sample\_decompressed.txt

````

---

## ⚙️ How to Run

### ✅ Install zlib (if not already installed)

**On Linux (Ubuntu/Debian):**
```bash
sudo apt-get install zlib1g-dev
````

**On Windows:**

* Download zlib from: [https://zlib.net/](https://zlib.net/)
* Link `zlib.lib` or `zlib.dll` in your compiler or IDE (e.g., Code::Blocks or Visual Studio)

---

### 🔨 Compile the Code

Using `g++` with zlib and threading:

```bash
g++ main.cpp -o file_tool -lz -pthread
```

---

### ▶️ Run the Program

```bash
./file_tool
```

---

### Sample Menu

```
=== FILE COMPRESSOR ===
1. Compress File
2. Decompress File
3. Exit
```

---

## 🛠 Tech Stack

* **Language:** C++
* **Compression Library:** zlib
* **Concurrency:** std::thread (C++11)
* **File I/O:** fstream

---

