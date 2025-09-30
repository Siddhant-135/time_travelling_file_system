sab kucch padhegi hain ? compile karna nahi aata pehle se ? besharam

# Time-Travelling File System

A simple, in-memory version control system for files, written in C++. You can create files, make changes, view history, branch, and roll back to earlier versions—all from the command line.

---

### Build & Run on Linux/Mac

```bash
chmod +x compile.sh
./compile.sh
./program
```
---

Type EXIT to quit the program (or, like, control + C)

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


## Error Handling: Common errors and good practices

If you make errors, thats on you. This code will just ignore it and move ahead like nothing happened.
Update pending to make this more fool-proof.

bye !
