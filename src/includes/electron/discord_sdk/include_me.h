#pragma once
#define MAX_NAME 124
#define _NO_REPRO_PADDING

#include "../../../includes.hpp"

class DiscordObject {
  public:
    std::time_t epoch;
    
    bool bLocallyOwned;
    bool bPermanent;
    bool bHTMLRelated;
    
    std::string string_identifier;
    std::string relative_queue;
    
    int alternative_identifier;
    int _useless_var;
};

struct UGeolocationData {
    uint32_t idx;
    
    char gLocationDataFormatted[512];
    
    // * unofficial
    PAD(0x80);
    
    std::string City;
    std::string PostCode;
    std::string Street;
    std::string Country;
    
    char* ACompileData(char* formattedData, BOOL return_formatted_sep = TRUE);
    
    std::time_t timestamp;
};

struct FLocalnameEntry 
{
    uint32_t RegularIndex;
    uint32_t Padding;
    
    FLocalnameEntry* gathered_information;
    
    union 
    {
        wchar_t Localname[MAX_NAME]; // 124  
    };
    
    const char* AGetLocalname(); // ansi format
    const wchar_t* GetLocalname(); // wide
};

struct DiscordClient {
    PAD(0x100);
    unsigned char AccountType; // : 1
    PAD(0x32);
    struct FUsernameEntry;
    
    const int GetIdx();
    const char* GetSecondaryIdx();
    
    PAD(0x35); /* Geolocation requires access to local user IP, using this will geolocate yourself. */
    
    BOOL GeolocatePosition(UGeolocationData* gData);
    
    
};

class TIndexArray
{
  public:
    bool IsValidIndex(uint32_t index);
    
    FLocalnameEntry const* GetIndexByID(uint32_t identifier, bool spoof_call = 0);
    FLocalnameEntry* GetIndexPtr(uint32_t index);
    PAD(0x50);
    
    FLocalnameEntry** ALocalname_example;
    AllocMemoryChunks(uint32_t* indexptr);
    
    union
    {
        unsigned char* chunk_repro;
        char ChunkLazyLoad[256];
        
        uint32_t _unknown;
    };
    PAD(0x10);
    
    uint32_t chunkByteSize[512];
}

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

// Size = 0x0008
class DiscordUser : public DiscordObject
{
    char* ElectronDefaultInterface;
    PAD(0x10);
    bool PrivCheck(int flag_id); // check privs in current guild
    
    PAD(0x30);
    PAD(0x15);
    PAD(0x50);
    PAD(0x30);
    
    bool create_temp_role(uint32_t secs, const char* role_name, int flag_id);
    bool assign_role(DiscordUser* user, const char* role_name, int _unused, int __unused); // update main
    
    uint32_t send_pkt(DiscordVoip* voip, std::string data, unsigned int padding);
    
    BOOL admin;
};

class DiscordGuild : public DiscordObject
{
    // not perfect, needs fix
    char* ElectronDefaultInterface;
    
    BOOL RemoveGuild(DiscordUser* user);
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
    
    DiscordVoip get_joinable_vc( );
};


// Generated (0x0007) = (0x0001)
std::string GenerateJunk(uint32_t len);
