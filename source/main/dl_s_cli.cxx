#include "dl_s_cli.hxx"

/* Initialize our user interface and browse it */
int main()
{
    /* TODO - Load settings */
    std::unique_ptr<UI> ui = std::make_unique<UI>();

    /* Display a message when starting the program. If the user exits while in firstStart(), terminate the 
     * program */
    if (!ui->firstStart()) {
        return 1;
    }

    /* Navigate through dl_s_cli UI */
    {
        int ch = 0;
        bool resizeUI = false;

        while ((ch = getch()) != KEY_F(1)) {
            switch(ch) {
                case KEY_RESIZE:
                    {
                        resizeUI = true;
                        break;
                    }

                case KEY_DOWN:
                    {
                        /* TODO - Make sure that the menu is not empty */
                        if (1)/*(ui->controller->isActive())*/ {
                            ui->downloads_menu->menuDriver(REQ_DOWN_ITEM);
                            ui->statusDriver(KEY_DOWN);
                        }
                        break;
                    }

                case KEY_UP:
                    {
                        /* TODO - Make sure that the menu is not empty */
                        if (1) /*(ui->controller->isActive())*/ {
                            ui->downloads_menu->menuDriver(REQ_UP_ITEM);
                            ui->statusDriver(KEY_UP); 
                        }
                        break;
                    }

                case 10:
                    /* Enter - user has selected an item */
                    {

                        /* TODO - Make sure that the menu is not empty */
                        if (1) /*(!ui->controller->isActive())*/ {
                            break;
                        }
                        ui->stopStatusUpdate();

                        /* showDetails returns true if the download was killed and that we should update the
                         * menu */
                        if (ui->showDownloadDetails(ui->downloads_menu->getItemName())) {
                            ui->updateDownloadsMenu();
                            ui->resetStatusDriver();
                            ui->main_windows.at(ui->status_window_index)->resetWin();
                        }

                        ui->startStatusUpdate(); 
                        break;
                    }

                case 'a':
                    /* Opens a subwindow in which we'll enter the new download item info */
                    {
                        ui->stopStatusUpdate();
                        if (ui->addNewDownload()) {
                            ui->updateDownloadsMenu();
                            ui->resetStatusDriver();
                        }
                        ui->startStatusUpdate();
                        break;
                    }

                case 'h':
                    {
                        ui->stopStatusUpdate();
                        if (ui->showHelp()) {
                            ui->updateDownloadsMenu();
                            ui->resetStatusDriver();
                        }
                        ui->startStatusUpdate();
                        break;
                    }

                case 's':
                    {
                        ui->stopStatusUpdate();
                        if (ui->showSettings()) {
                            ui->updateDownloadsMenu();
                            ui->resetStatusDriver();
                        }
                        ui->startStatusUpdate();
                        break;
                    }
                case 'p':
                    /* TODO - Pause highlighted download */
                    {
                        if (1) /*(!ui->controller->isActive())*/ {
                            break;
                        }
                        //ui->controller->pause(ui->downloads_menu->getItemName());
                        break;
                    }

                case 'P':
                    /* TODO - Pause all active downloads */
                    {
                        if (1) /* (!ui->controller->isActive())*/ {
                            break;
                        }
                        ui->stopStatusUpdate();
                        //ui->controller->pauseAll();
                        ui->startStatusUpdate();
                        break;
                    }

                case 'r':
                    /* TODO - Resume selected download */
                    {
                        if (1) /*(!ui->controller->isActive())*/ {
                            break;
                        }
                        ui->stopStatusUpdate();
                        //ui->controller->resume(ui->downloads_menu->getItemName());
                        ui->startStatusUpdate();
                        break;
                    }
                case 'R':
                    /* TODO - Resume all paused downloads */
                    {
                        if (1) /*(!ui->controller->isActive())*/ {
                            break;
                        }
                        ui->stopStatusUpdate();
                        //ui->controller->resumeAll();
                        ui->startStatusUpdate();
                        break;
                    }

                case 'c':
                    /* TODO - Clear inactive transfers */
                    {
                        if (1) /*(!ui->controller->isActive())*/ {
                            break;
                        }
                        ui->stopStatusUpdate();
                        //ui->controller->clearInactives();
                        ui->main_windows.at(ui->status_window_index)->resetWin();
                        ui->updateDownloadsMenu();
                        ui->resetStatusDriver();
                        ui->startStatusUpdate();
                        break;
                    }

                case 'k':
                    /* TODO - Kill selected download */
                    {
                        if (1) /*(!ui->controller->isActive())*/ {
                            break;
                        }
                        ui->stopStatusUpdate();
                        //ui->controller->stop(ui->downloads_menu->getItemName()); 
                        ui->updateDownloadsMenu();
                        ui->resetStatusDriver();
                        ui->main_windows.at(ui->status_window_index)->resetWin();
                        ui->startStatusUpdate();
                        break;
                    }

                case 'K':
                    /* TODO - Kill all downloads */
                    {
                        if (1) /*(!ui->controller->isActive())*/ {
                            break;
                        }
                        ui->stopStatusUpdate();
                        //ui->controller->killAll();
                        ui->updateDownloadsMenu();
                        ui->main_windows.at(ui->status_window_index)->resetWin();
                        ui->startStatusUpdate();
                        break;
                    }

                case CTRL('z'):
                    /* TODO - catch sigint - exit gracefully */
                    {
                        break;
                    }

                default:
                    {
                        break;
                    }
            }
            if (resizeUI) {
                ui->stopStatusUpdate();
                ui->resizeUI();
                ui->updateDownloadsMenu();
                ui->resetStatusDriver();
                ui->startStatusUpdate();
                resizeUI = false;
            }

            /* Consistantly update main windows */
            {
                std::lock_guard<std::mutex> guard(ui->downloads_infos_window_mutex);
                ui->refreshMainWindows();        
            }
        }
    }
    return 0;
}

