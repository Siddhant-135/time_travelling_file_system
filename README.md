# Time-Travelling File System

A simple, in-memory version control system for files, written in C++. You can create files, make changes, view history, branch, and roll back to earlier versions—all from the command line.

---

## Getting Started

### Requirements

- *C++17 or later* 

### Build & Run on Linux/Mac

```bash
chmod +x compile.sh
./compile.sh
./executable
```
\\ IMPORTANT: depending on where the executable file is generated in your folder structure, you may need to travel up by using 
```bash
cd .. 
```
to access the parent directory.
---


## What Can You Do?

- **CREATE \<filename>**: Make a new file (starts at version 0)
- **READ \<filename>**: Show the current content
- **INSERT \<filename> \<content>**: Add content (creates a new version)
- **UPDATE \<filename> \<content>**: Replace content (creates a new version)
- **SNAPSHOT \<filename> \<message>**: Mark the current version with a message
- **ROLLBACK \<filename> [versionID]**: Go back to a previous version (by ID or just the previous one)
- **HISTORY \<filename>**: See all versions and their messages
- **RECENT_FILES [num]**: List the most recently changed files
- **BIGGEST_TREES [num]**: List files with the most versions

---

## How to Use

Here are some example commands you can use in the system:

```
CREATE document.txt
INSERT document.txt Hello World
SNAPSHOT document.txt First draft
# Output Format: Snapshot created: Version 1 at 2025-09-11 12:48:10

INSERT document.txt \nSecond line 
#using \n tells it to go to the second line
UPDATE document.txt Updated content
HISTORY document.txt
ROLLBACK document.txt 0
READ document.txt
RECENT_FILES 5
BIGGEST_TREES 3
```

Type `exit` or `EXIT` to quit.

---

## Error Handling: Common errors and good practices

This system tries to catch common mistakes and gives you clear feedback:

### File Commands
- **Filenames can't have spaces.** If you try, you'll see: `Error: Invalid filename 'name'. Filenames cannot contain whitespace.`
- **File not found?** You'll get a message if you try to use a file that doesn't exist.
- **No overwriting files.** If you try to CREATE a file that already exists, you'll get an error.
- **Missing info?** If you forget a required part of a command, the system will let you know.

### ROLLBACK
- **Version out of range?** You'll see an error if you try to roll back to a version that doesn't exist, such as rolling back from the root
- **Not a number?** If you give a non-number as a version, you'll get a format error.
- **Can't roll back from the first version.** The system will warn you if you try.

### Analytics (RECENT_FILES, BIGGEST_TREES)
- **No files yet?** The system handles empty lists gracefully.
- **Invalid number?** Negative or zero counts are rejected.
- **Too many requested?** If you ask for more files than exist, it tells you how many it showed, adn that no more exist.
- **Ties?** If there's a tie, files are sorted alphabetically and you'll be told.

### Input Checks
- **Filenames:** No spaces allowed.
- **Version IDs:** Must be numbers: no brackets or weird symbols.
- **SNAPSHOT:** Needs a message. (I hate coworkers who dont attach comments to their pushes on github)
- **Content:** Handles empty or whitespace content properly.

The system checks for common mistakes and gives clear error messages. Here are some examples:

---

### Tie-Breaking Rules
- Recent files: Sorted by modification time (desc), then alphabetically (asc)
- Biggest trees: Sorted by version count (desc), then alphabetically (asc)
- System reports when ties are broken for transparency
