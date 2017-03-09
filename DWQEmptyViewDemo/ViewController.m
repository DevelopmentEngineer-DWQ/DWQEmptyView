//
//  ViewController.m
//  DWQEmptyViewDemo
//
//  Created by 杜文全 on 16/9/9.
//  Copyright © 2016年 com.iOSDeveloper.duwenquan. All rights reserved.
//

#import "ViewController.h"
#import "UIView+DWQEmptyView.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    
//        //如果无网络
//        [self.view showErrorPageView];
//        [self.view configReloadAction:^{
//            NSLog(@"点击我就可以刷新了啊");
//        }];
    
         //空数据
           [self.view showBlankPageView];
        //隐藏
        //[self.view hideBlankPageView];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
