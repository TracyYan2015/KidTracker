#import <QuartzCore/QuartzCore.h>

#import "CCDirector.h"
#import "CCEAGLView.h"

#import "ImagePicker.h"
#import "ImagePickerIOS.h"
#import <UIKit/UIKit.h>

@implementation ImagePickerIOS

-(void) takePicture
{
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    [imagePicker setSourceType:UIImagePickerControllerSourceTypePhotoLibrary];
    [imagePicker setDelegate:self];
    imagePicker.wantsFullScreenLayout = YES;
    CCEAGLView *view = (CCEAGLView *)cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView();
    
    UIPopoverController * photoPop=[[UIPopoverController alloc] initWithContentViewController:imagePicker];
    [photoPop presentPopoverFromRect:CGRectMake(0,0,view.frame.size.width, view.frame.size.height/2) inView:view permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
    //[picker release];

    
    //[view addSubview:imagePicker.view];
}

-(void) imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
    
    cocos2d::Image *imf =new cocos2d::Image();
    imf->autorelease();
    
    @autoreleasepool
    {
        NSData *imgData = UIImagePNGRepresentation(image);
        NSUInteger len = [imgData length];
        
        Byte *byteData = (Byte*)malloc(len);
        memcpy(byteData, [imgData bytes], len);
    
        imf->initWithImageData(byteData, len);
        
        free(byteData);
    }
    
    cocos2d::Texture2D* pTexture = new cocos2d::Texture2D();
    pTexture->initWithImage(imf);
    pTexture->autorelease();

    ImagePicker::getInstance()->finishImage(pTexture);
    
    [picker.view removeFromSuperview];
    [picker release];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    ImagePicker::getInstance()->finishImage(nullptr);
    [picker.view removeFromSuperview];
    [picker release];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
