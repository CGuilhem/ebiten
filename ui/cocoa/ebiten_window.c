// -*- objc -*-

#import "ebiten_window.h"

#include <OpenGL/gl.h>

#import "ebiten_content_view.h"

@implementation EbitenWindow

- (id)initWithSize:(NSSize)size {
  NSUInteger style = (NSTitledWindowMask | NSClosableWindowMask |
                      NSMiniaturizableWindowMask);
  NSRect windowRect =
    [NSWindow frameRectForContentRect:NSMakeRect(0, 0, size.width, size.height)
                            styleMask:style];
  NSScreen* screen = [[NSScreen screens] objectAtIndex:0];
  NSSize screenSize = [screen visibleFrame].size;
  // Reference: Mac OS X Human Interface Guidelines: UI Element Guidelines:
  // Windows
  // http://developer.apple.com/library/mac/#documentation/UserExperience/Conceptual/AppleHIGuidelines/Windows/Windows.html
  NSRect contentRect =
    NSMakeRect((screenSize.width - windowRect.size.width) / 2,
               (screenSize.height - windowRect.size.height) * 2 / 3,
               size.width, size.height);
  self = [super initWithContentRect:contentRect
                          styleMask:style
                            backing:NSBackingStoreBuffered
                              defer:YES];
  assert(self != nil);
  [self setReleasedWhenClosed:YES];
  [self setDelegate:self];
  [self setDocumentEdited:YES];

  NSRect rect = NSMakeRect(0, 0, size.width, size.height);
  NSView* contentView = [[EbitenContentView alloc] initWithFrame:rect];
  [self setContentView:contentView];

  return self;
}

- (BOOL)windowShouldClose:(id)sender {
  if ([sender isDocumentEdited]) {
    // TODO: add the application's name
    NSAlert* alert = [NSAlert alertWithMessageText:@"Quit the game?"
                                     defaultButton:@"Quit"
                                   alternateButton:nil
                                       otherButton:@"Cancel"
                         informativeTextWithFormat:@""];
    SEL selector = @selector(alertDidEnd:returnCode:contextInfo:);
    [alert beginSheetModalForWindow:sender
                      modalDelegate:self
                     didEndSelector:selector
                        contextInfo:nil];
    [alert release];
  }
  return NO;
}

- (void)alertDidEnd:(NSAlert*)alert
         returnCode:(NSInteger)returnCode
        contextInfo:(void*)contextInfo {
  (void)alert;
  (void)contextInfo;
  if (returnCode == NSAlertDefaultReturn) {
    [NSApp terminate:nil];
  }
}

- (BOOL)canBecomeMainWindow {
  return YES;
}

@end
