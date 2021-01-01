// TODO - most actions will (probably) be done on nas postgres database
#include "../include/Settings.hxx"

// Load system info from Environment.
Settings::Settings()
    :username(Environment::getUsername()),  home_dir("/Users/" + username + "/")
     ,cpu_count(Environment::getCPUCount())
{}

Error Settings::load()
{
    /* TODO - 
     *      Check if .conf exists in config/
     *      If .conf -> read settings and copy them into the variables 
     *      Else create default values using system information.
     */
    return setDefaults();
}

// TODO - Needed ?
Error Settings::setDefaults()
{
    Error err;

    // dl_s_cli compatible
    max_simultaneous_transfers = cpu_count;
    // TODO - works for torrents, not for DDLs
    //max_down_speed = 0;
    //max_up_speed = 0;
    // TODO - default download dir (/volume1/some_folder)
    downloads_dir = home_dir + "Downloads/tinyDownloads/";
    // Directory path displayed in UI uses ~ notation if possible - No tilde in NAS ?
    displayed_downloads_dir = Environment::tildefyPath(home_dir, downloads_dir);
    Error dir_err = setDownloadsDirectory(downloads_dir);

    if (dir_err.code != ErrorCode::dir_creat_err) {
        writeConfigFile(home_dir, downloads_dir, std::to_string(max_transfer_speed), std::to_string(max_simultaneous_transfers));

        err.code = ErrorCode::first_start_ok;
        err.message = msgNewUserOk; 
    }
    else {
        err.code = ErrorCode::first_start_err;
        err.message = msgNewUserErr;
    }

    return err;
}

// TODO - read/write nas config file (probably in a db as well)
void Settings::writeConfigFile(const std::string& h_dir, const std::string& dir, const std::string& max_speed, const std::string& max_sim_trans)
{
    const std::string conf_file_path = h_dir + ".dl_s_cli";
    FileIO(conf_file_path) << "downloads_directory=" << dir <<
                              "\nmax_download_speed=" << max_speed << 
                              "\nmax_simultaneous_transfers=" << max_sim_trans;
}

// Returns true if the path returned a valid directory. Else signal error in settings window.
Error Settings::setDownloadsDirectory(const std::string& p)
{
    Error err;

    const std::string full_path = Environment::expandTilde(home_dir, p);

    if (Environment::directoryExists(full_path)) {
        err.code = ErrorCode::dir_exists_err;
        err.message = "Directory already exists.";
        downloads_dir = full_path;
    }
    else {
        err = Environment::createDirectory(full_path);
        if (err.code == ErrorCode::dir_creat_ok) {
            err.code = ErrorCode::err_ok;
            downloads_dir = full_path;
        }
    }

    displayed_downloads_dir = Environment::tildefyPath(home_dir, downloads_dir);

    return err;
}

Error Settings::setMaximumTransferSpeed(const double& speed)
{
    Error err;
    return err;
}

Error Settings::setMaximumSimultaneousTransfers(const int& number) 
{
    Error err;
    return err;
}

std::string Settings::getDisplayedDownloadsDirectory()
{
    return displayed_downloads_dir;
}

std::string Settings::getDownloadsDirectory()
{
    return downloads_dir;
}

/* TODO - use an unsigned 64 bit here */
double Settings::getMaximumTransferSpeed()
{
    return max_transfer_speed;
}

int Settings::getMaximumSimultaneousTransfers()
{
    return max_simultaneous_transfers;
}


// TODO - move to helper functions
// Convert absolute path to ~ path if path is in $HOME


