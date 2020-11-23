//
//  MainViewController.m
//  filament_build
//
//  Created by Erik Toth on 2020. 10. 20..
//

#import "MainViewController.h"
#import "apeFilamentRenderMacPlugin.h"


@interface MainViewController ()

@end


@implementation MainViewController

-(id)initWithNibName:(NSString*)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self){
        //initialize code here
    }
    return self;
}


using namespace ape;

-(void)awakeFromNib{
    ape::FilamentRenderMacPlugin apeFilament(self.view);
}
    

@end
