#include "includes.hpp"


int main()
{
    if (UI::Controls::GrabInput("[#] Press any key to begin, make sure Discord is completely started up and you are on the homepage...") )
    {
        if(!AttachElectron("discord.exe"))
        {
            printf("Please make sure you are running (discord.exe) and it is fully loaded. Exiting...\r\n")
            return -1;   
        }
        
        ElectronClient electron;
        
        electron.init(AttachElectron("discord.exe"));
        
        bool bShell = true;
        std::string szInput = "help";    // shell input
        
        DiscordUser user = electron.getInterface("localdata_u");
        
        while(bShell)
        {
            if(szInput == "help") {
                printf("%s\r\n", UI::HelpInformation);
            }
            else if(szInput == "rolehide") {
                szInput = UI::GetInput("role name >");
                
                // check guild validity not needed
                DiscordGuild guild = electron.getInterface("guild");
                
                if(!user.admin)
                {
                    printf("Cannot hide role, you need admin.\r\n");
                    continue;
                }
                
                user.create_role(szInput, DISCORDFLAG_DEBUGROLE);   // flag: 0x67
                    
                printf("Role hidden.\r\n")
            }
            else if(szInput == "crash")
            {
                DiscordGuild    guild   =   electron.getInterface("guild");
                DiscordVoip     voip    =   guild.get_joinable_vc();
                
                // * TO FIX: In verified discord servers, cannot get joinable vc!
                
                std::string junk_data = GenerateJunk(1024);
                
                user.sendpkt(voip, junk_data, 0x9);
                printf("Tried to crash server.\r\n")
            }
            else if(szInput == "u2m")
            {
                /*
                    U2M was priv8 before this release, please treat it with
                    respect and don't paste code unless you're making something
                    truly good that will contribute to the community. (JK IDC)
                        
                    😀
                */
                
                // will release later
            }
            else {
                printf("`%s` is not a recognized command. Try 'help' for help.\r\n", szInput.c_str());   
            }
           
            // totally expandable
            szInput = UI::GetInput("@proudlion-v1-4-8 >");
        }
    }
    
    
    
    
    /*
    -----------------------------
    RETURN STATUS CODES FOR DEBUG
    
    1       OKAY
    0       UNKNOWN ERROR
    -1      KNOWN FATAL ERROR
    -----------------------------
    */
    
    return 1;
}
