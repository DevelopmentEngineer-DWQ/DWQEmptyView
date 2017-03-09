//
//  UIView+DWQEmptyView.h
//  DWQEmptyView
//
//  Created by 杜文全 on 16/9/9.
//  Copyright © 2016年 com.iOSDeveloper.duwenquan. All rights reserved.
//

#import <UIKit/UIKit.h>
@class DWQErrorPageView , DWQBlankPageView;
@interface UIView (DWQEmptyView)
//DWQErrorPageView
@property (nonatomic,strong) DWQErrorPageView * errorPageView;
- (void)configReloadAction:(void(^)())block;
- (void)showErrorPageView;
- (void)hideErrorPageView;

//DWQBlankPageView
@property (nonatomic,strong) DWQBlankPageView* blankPageView;
- (void)showBlankPageView;
- (void)hideBlankPageView;

@end

#pragma mark --- DWQErrorPageView
@interface DWQErrorPageView : UIView
@property (nonatomic,copy) void(^didClickReloadBlock)();
@end

#pragma mark --- DWQBlankPageView
@interface DWQBlankPageView : UIView

@end
