# OldWay 🛑

Just a simple C++ script that bans AI chat bots and tools because I'm missing the old days with no AI. :)

No magic frameworks, no auto-generated boilerplate. This is just pure C++ that modifies your system's `/etc/hosts` file to block known AI domains and instantly flushes your DNS. It forces you to close the AI tabs, read the docs, and actually write your own code.

**⚠️ Currently tested on macOS only** 
## ⚙️ Customize Your Blocklist

You don't have to block everything. You can easily enable or disable specific AI tools by editing the `banList` map in `Main.cpp`.

Just change `true` to `false` next to any tool you want to keep using, and re-run the script.
```cpp
banList = {
    {"chatgpt.com", true},
    {"gemini.google.com", true},
    {"openai.com", true},
    {"claude.ai", true},
    // ... more domains
};
```

## 🚀 How to Use

Make sure you have `g++` and `make` installed.

**To block AI and get to work:**
```bash
make run
```

(Note: Because this modifies system files and flushes the macOS DNS cache, it will prompt for your sudo password).

**To restore your original hosts file (if you really need to):**
```bash
make backup
```

## 🤝 Contribute

Are you also missing the old days? Help make this better.

- **Add domains:** Find an AI site that isn't blocked? Add it to the `banList` in `Main.cpp`.
- **Add OS support:** Currently, the instant DNS flush is built for macOS. Feel free to add pure C++ implementations for Linux or Windows.

Fork the repo, write some pure code, and submit a PR.