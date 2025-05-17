# Heuristic Rush Hour Solver

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/username/rush-hour-solver)
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)
[![C++](https://img.shields.io/badge/language-C++17-blue)](https://isocpp.org/)

## Deskripsi
Proyek ini adalah solver untuk permainan **Rush Hour** menggunakan berbagai algoritma pencarian seperti Uniform Cost Search (UCS), Greedy Best-First Search (GBFS), A*, dan Beam Search. Proyek ini mendukung pemilihan heuristic yang berbeda dan menampilkan solusi langkah demi langkah dengan visualisasi warna pada terminal.

---

## Cara Menjalankan

### Prasyarat
- Compiler C++17 atau lebih baru
- Make (build automation tool)

### Build dan Run
1.  **Build proyek** dengan perintah:
    ```bash
    make build
    ```
2.  **Jalankan program** menggunakan:
    ```bash
    make run
    ```
3.  Program akan meminta input:
    -   Nama file input (diletakkan di folder `test/input/`)
    -   Pilih algoritma pencarian:
        1.  Greedy Best-First Search
        2.  Uniform Cost Search
        3.  A* Search
        4.  Beam Search
    -   Pilih heuristic
4.  Setelah selesai, program akan menampilkan langkah solusi di terminal dan menanyakan nama file untuk menyimpan output (disimpan di `test/output/`).

---

## Struktur Folder
```
.
├── include/           # Header files
├── src/               # Source code
├── test/
│   ├── input/         # File input puzzle
│   └── output/        # File output solusi
├── Makefile           # Skrip build
└── README.md          # Dokumen ini
```

---

## Kontribusi
| Nama                | NIM         |
| :------------------ | :---------- |
| Muhammad Fathur Rizky | 13523105 |

---

## Lisensi
Proyek ini dilisensikan di bawah MIT License. Lihat file [LICENSE](LICENSE) untuk informasi lengkap.