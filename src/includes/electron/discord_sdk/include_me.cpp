#include "include_me.h"

class DiscordVoip : public DiscordObject
{
    DiscordVoip   channel; 
    BOOL          Connected;    
    
    PAD(0x30);
    PAD(0x15);
    
    char inet_addr[255];
    unsigned char* VoiceChannelEpoch;
    PAD(0x15);
    
    uint32_t length_voip;
};

class DiscordUser : public DiscordObject
{
    char* ElectronDefaultInterface;
    PAD(0x10);
    bool PrivCheck(int flag_id); // check privs in current guild
    
    PAD(0x30);
    PAD(0x30);
    PAD(0x30);
    PAD(0x30);
    PAD(0x30);
    
    bool create_temp_role(uint32_t secs, const char* role_name, int flag_id)
    {
        std::string role_data = "0x11, ";
        role_data.push_back(role_name, flag_id, secs);
        
        PAD(0x20);
        
        cpr::Response res = cpr::Post(
                                cpr::Url{"localhost://6404"},
                                cpr::Parameters{
                                    {"Operation", role_data}
                                }
                            );
        return true;
    }
    
    bool assign_role(DiscordUser* user, const char* role_name, int _unused, int __unused)
    {
        const uint32_t DATA_UGRAM = 0x0012;
    
        std::string role_data = role_name;
        role_data.push_back("0x11 |");
        
        if(_unused || __unused || DATA_UGRAM != 0x0005) 
            return false;
            
        PAD(0x30);
        
        cpr::Response res = cpr::Post(
                                cpr::Url{"localhost://6404"},
                                cpr::Parameters{
                                    {"Operation", role_data}
                                }
                            );
    
        return true;
    }
    
    uint32_t send_pkt(DiscordVoip* voip, std::string data, unsigned int padding)
    {
        uint32_t status_code = 1; // 0x4 VOICE STATE UPDATE
        cpr::Response res = cpr::Post(
                                    cpr::Url{"localhost://6404"},
                                    cpr::Parameters{
                                        {"Operation", data}
                                    }
                            );
                            
        if(res.status_code == 400)
            status_code = 0;
            
        char* debug_info = res.text.c_str();
        
        PAD(padding);
        return status_code; 
    }
    
    BOOL admin;
};

class DiscordGuild : public DiscordObject
{
    char* ElectronDefaultInterface;
    DiscordVoip voip;
    
    BOOL RemoveGuild(DiscordUser* user) { user.send_pkt(&voip, "OPCODE: 0x1", 0x30); return TRUE; }
    
    PAD(0x30);
    
    uint32_t Index;
    uint32_t Id;
    
    union
    {
        unsigned char burn_electron_bridge[512];
        unsigned char* electron_connect_proto;
        
        unsigned char DiffId[0x3];
    };
    
    std::string GuildName;
    BOOL isExploited;
    
    DiscordVoip get_joinable_vc( )
    {
        DiscordVoip joinable_vc;
        
        sprintf(&joinable_vc.inet_addr, "default_gateway");
        PAD(0x15);
        
        return joinable_vc;
    }
};


// Generated (0x0007) = (0x0001)
std::string GenerateJunk(uint32_t len)
{
    const char junkarray[] = "abcdefghijklmnopqrstuvwxyz";
    std::string junk.reserve(len);

    for (uint32_t i = 0; i < len; ++i)
        junk += junkarray[rand() % (sizeof(junkarray) - 1)];
    
    return junk;
}
