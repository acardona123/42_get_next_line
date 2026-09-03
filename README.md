<h1 align="center">get_next_line</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white" alt="C"/>
</p>

<p align="center"><strong>A function that reads a file line by line, one buffer-sized <code>read()</code> at a time, remembering where it left off between calls.</strong></p>

---

## 📌 Overview

`read()` gives back an arbitrary chunk of bytes, not a line, so turning a file descriptor into a sequence of lines means holding on to whatever came after the last newline until the caller asks for more.
get_next_line does that with a single static buffer that survives between calls: each call tops it up with fixed-size reads until a `\n` shows up, hands back everything up to it, and keeps the remainder for next time.
The mandatory version only has to track one file descriptor at a time; the bonus version has to do the same thing for several files read out of order without mixing up their leftovers.

## 🎯 Objectives

- Return one line per call from a file descriptor, without ever reading past what has actually been requested
- Work for any `BUFFER_SIZE` compiled in, from 1 byte to far more than a typical line
- Return `NULL` once the descriptor is exhausted, and handle a read error the same way
- Bonus: keep several file descriptors independently readable at once, each remembering its own unread remainder

## 🧠 How it works

The mandatory `get_next_line` keeps one `static t_buffer` (a fixed-size `char` array plus a start and end index into it).
On each call it refills the buffer with `read()` until either the buffer holds a `\n` or the file is exhausted, joining every full buffer it consumes onto the string it is building.
Once a `\n` is found, it slices out everything up to and including it, leaves the rest sitting in the buffer for the next call, and returns.

The bonus version replaces that single static buffer with a fixed array of 1024 of them, `static t_buffer buff[1024]`, and indexes directly into it by file descriptor.
That is an array, not a linked list: any fd under 1024 gets its own permanent slot, so two files (or a file and `stdin`) can be read line by line in any interleaving without their partial buffers colliding.
The trade-off is that the array is sized for the whole fd range up front rather than growing with however many files are actually open.

## 🛠️ Tech Stack

<p>
  <img src="https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white" alt="C"/>
</p>

## 🚀 Getting Started

```bash
git clone https://github.com/acardona123/42_get_next_line.git
cd 42_get_next_line
cc -I. -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_main.c
```

## 📖 Usage

```bash
# mandatory
cc -I. get_next_line.c get_next_line_utils.c tests/maintest.c -D BUFFER_SIZE=11 -o a.out
cd tests && ../a.out -1

# bonus
cc -I. get_next_line_bonus.c get_next_line_utils_bonus.c tests/maintest.c -D BUFFER_SIZE=11 -o a.out
cd tests && ../a.out 3
```

`get_next_line` takes an open file descriptor and returns the next line, newline included, or `NULL` once there is nothing left to read.

## 🧪 Tests

`tests/maintest.c` drives both variants against `tests/text.txt` and `tests/text1.txt` through five cases selected by its argument: an invalid fd, `stdin`, a single file read line by line, the same file read in one call, and two files read interleaved (bonus only).
Validated against [42_tester_get_next_line](https://github.com/acardona123/42_tester_get_next_line), which runs the mandatory and bonus builds across a range of `BUFFER_SIZE` values.

## 📚 Resources

- [fr.subject.pdf](fr.subject.pdf)

---

<p align="center"><sub>🏫 Project from the <strong>42</strong> common core, School 42 Paris.</sub></p>
