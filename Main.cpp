//
// Created by Kooneo on 14/2/2026.
//

#include "Main.hpp"

const std::string localhostIp = "127.0.0.1";

std::unordered_map<std::string, bool> banList;

void prepareBanList()
{
    banList = {
        {"chatgpt.com", true},
        {"gemini.google.com", true},
        {"openai.com", true},
        {"claude.ai", true},
        {"perplexity.ai", true},
        {"chat.deepseek.com", true},
        {"gemini.google.com", true},
        {"copilot.microsoft.com", true},
        {"meta.ai", true},
        {"x.com/grok", true},
        {"poe.com", true},
        {"duckduckgo.com/chat", true},
        {"chat.vercel.ai", true},
        {"phind.com", true},
        {"blackbox.ai", true},
        {"chat.mistral.ai", true},
        {"huggingface.co/chat", true},
        {"groq.com", true},
        {"character.ai", true},
        {"c.ai", true},
        {"pi.ai", true},
        {"replika.com", true},
        {"you.com", true},
        {"chat.lmsys.org", true},
        {"ora.ai", true},
        {"flowgpt.com", true},
        {"coze.com", true},
        {"venice.ai", true},
        {"chat.qwenlm.ai", true},
        {"deepai.org", true},
        {"chatsonic.com", true},
        {"kuki.ai", true},
        {"cleverbot.com", true},
        {"janitorai.com", true},
        {"spicychat.ai", true},
        {"crushon.ai", true},
        {"figgs.ai", true},
        {"yodayo.com", true},
        {"chattica.ai", true},
        {"talkai.info", true},
        {"aichatting.net", true},
        {"yeschat.ai", true},
        {"monica.im", true},
        {"harpa.ai", true},
        {"luzia.com", true},
        {"hix.ai", true},
        {"cici.ai", true},
        {"maxai.me", true},
        {"sider.ai", true},
        {"typingmind.com", true},
        {"chatbotui.com", true},
        {"chatpad.ai", true},
        {"bettergpt.chat", true},
        {"chatpdf.com", true},
        {"askyourpdf.com", true},
        {"humata.ai", true},
        {"console.anthropic.com", true},
        {"platform.openai.com", true},
        {"aistudio.google.com", true}
    };
}

std::string defineTheHostsFilePath()
{
    std::string hostsFilePath;

#if (defined(__APPLE__) && defined(__MACH__) ) || defined(__linux__) || defined(__unix__) || defined(__unix)
    hostsFilePath = "/etc/hosts";
#else
    std::cout << "Unknown operating system." << std::endl;
    return "";
#endif
    return hostsFilePath;
}

void flushDNS() {
    std::cout << "Flushing macOS DNS cache..." << std::endl;

    int result = std::system("dscacheutil -flushcache; killall -HUP mDNSResponder");

    if (result == 0)
        std::cout << "DNS flushed successfully. AI is now blocked." << std::endl;
    else
        std::cerr << "Warning: Failed to flush DNS. You might need to restart your browser." << std::endl;
}

void makeHotsBackup(const std::string& hostsFilePath)
{
    try
    {
        std::filesystem::path backupDir = std::filesystem::current_path() / "backup";

        std::filesystem::create_directories(backupDir);
        std::filesystem::path destPath = backupDir / "hosts.backup";
        std::filesystem::copy_file(hostsFilePath, destPath, std::filesystem::copy_options::overwrite_existing);
    }
    catch (std::exception& e)
        std::cerr << "Error copying file: " << e.what() << std::endl;
}

std::string loadHostsFileContent(const std::string& hostsFilePath)
{
    std::ifstream hostsFile(hostsFilePath, std::ios::binary);

    if (!hostsFile.is_open())
    {
        std::cerr << "Error opening file: " << hostsFilePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << hostsFile.rdbuf();
    return buffer.str();
}

void writeBansToFile(const std::string& path, const std::string &hostsFileContent)
{
    std::ofstream outFile(path, std::ios::app);
    if (outFile.is_open())
    {
        for (const auto& [domain, isActive] : banList)
        {
            if (isActive && hostsFileContent.find(domain) == std::string::npos)
            {
                outFile << localhostIp << "\t\t" << domain << "\n";
            }
        }
        std::cout << "Bans added successfully!" << std::endl;
    }
    else
        std::cerr << "Permission denied. Run with sudo!" << std::endl;
}

int main()
{
    const std::string hostsFilePath = defineTheHostsFilePath();
    if (hostsFilePath.empty())
        return EXIT_FAILURE;
    makeHotsBackup(hostsFilePath);
    std::string hostsFileContent = loadHostsFileContent(hostsFilePath);
    prepareBanList();
    writeBansToFile(hostsFilePath, hostsFileContent);
    flushDNS();
    return 0;
}
