#include "menu.h"

#ifdef __APPLE__
#import <Cocoa/Cocoa.h>

void setup_platform_menu(const std::string& app_name) {
    NSApplication* app = [NSApplication sharedApplication];
    NSMenu* menubar = [[NSMenu alloc] init];
    NSMenuItem* appMenuItem = [[NSMenuItem alloc] init];
    [menubar addItem:appMenuItem];
    [app setMainMenu:menubar];

    NSMenu* appMenu = [[NSMenu alloc] init];
    NSString* quitTitle = [NSString stringWithFormat:@"Quit %s", app_name.c_str()];
    NSMenuItem* quitItem = [[NSMenuItem alloc] initWithTitle:quitTitle
                                                      action:@selector(terminate:)
                                               keyEquivalent:@"q"];
    [appMenu addItem:quitItem];
    [appMenuItem setSubmenu:appMenu];
}
#endif