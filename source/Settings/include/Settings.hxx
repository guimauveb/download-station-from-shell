#include <filesystem>

#include "../../dialogs/include/dialogs.hxx"
#include "../../helper/include/Environment.hxx"
#include "../../Error/include/Error.hxx"
#include "../../helper/include/FileIO.hxx"

/* Settings are modified through the UI "Settings" window */
class Settings {
    public:
        /* Ran on dl_s_cli initialization - check if a .conf file is present, otherwise create one with defaults values
         * and use these values. */
        Settings();

        Error load();

        /* Setters and getters */
        Error setDownloadsDirectory(const std::string& p);
        Error setMaximumTransferSpeed(const double& speed);
        Error setMaximumSimultaneousTransfers(const int& number);

        std::string getDisplayedDownloadsDirectory();
        std::string getDownloadsDirectory();
        /* TODO - use an unsigned 64 bit here */
        double getMaximumTransferSpeed();
        int getMaximumSimultaneousTransfers();

    private:
        /* Defaults:
         *      - Downloads directory: /Users/<username>/Downloads
         *      - Maximum transfer speed: no limit
         *      - Maximum simultaneous transfers: number of cpu's
         * Defaults are obtained from Environment */
        Error setDefaults();
        std::string generateDefaultDownloadsFolder(const std::string& username);
        void writeConfigFile(const std::string& h_dir,const std::string& dir, const std::string& max_speed, const std::string& max_sim_trans);

        std::string username;
        std::string home_dir;
        std::string downloads_dir;
        std::string displayed_downloads_dir;
        uint64_t max_transfer_speed;
        int max_simultaneous_transfers;
        int cpu_count;
};
