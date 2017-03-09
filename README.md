# DWQEmptyView
没有网络，或者数据为空时提示页【仿淘宝】，超级好用
![DWQ-LOGO.jpeg](http://upload-images.jianshu.io/upload_images/2231137-4aa1d6e84e9da9f4.jpeg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##引述

我们在使用淘宝的时候，在我的订单页面，如果没有相应的订单状态，会有相应的提示，如下图为淘宝无订单时候的页面显示
![IMG_8963.PNG](http://upload-images.jianshu.io/upload_images/2231137-b4ad407d6ca30ace.PNG?imageMogr2/auto-orient/strip%7CimageView2/2/w/100)
其实，在我们整个的iOS开发过程中，不止这里会用到，当我们任何一个页面再没有数据时候都会有一个提示页，增加用户体验。于是本人对齐进行了封装，真正做到了哪里用到哪里调，简单的一行代码就可以完成这个效果。

##DWQEmptyView

每个人的实现方式不同，我是通过为UIvew添加分类，结合Runtime动态添加属性的方法实现空白视图效果的。实现原理主要点

- 1.在UIView分类的 .m 文件中关联对象（动态添加属性）

```objective-c
//DWQErrorPageView
- (void)setErrorPageView:(DWQErrorPageView *)errorPageView{
    [self willChangeValueForKey:NSStringFromSelector(@selector(errorPageView))];
    objc_setAssociatedObject(self, @selector(errorPageView), errorPageView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    [self didChangeValueForKey:NSStringFromSelector(@selector(errorPageView))];
}
- (DWQErrorPageView *)errorPageView{
    return objc_getAssociatedObject(self, _cmd);
}
```
ruantime方法介绍
> objc_setAssociatedObject(id object, const void *key, id value, objc_AssociationPolicy policy)
id object : 表示关联者，是一个对象
const void key: 获取被关联者的索引key
id value : 被关联者
objc_AssociationPolicy policy : 关联时采用的协议，有assign，retain，copy等协议，一般使用OBJC_ASSOCIATION_RETAIN_NONATOMIC


- 2.创建空白视图

```objective-c
- (instancetype)init{
    return [self initWithFrame:CGRectZero];
}
- (instancetype)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor whiteColor];
        
        UIImageView* errorImageView = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"DWQBlankPage"]];
        _errorImageView = errorImageView;
        [self addSubview:_errorImageView];
        
        UILabel* errorTipLabel = [[UILabel alloc]init];
        errorTipLabel.numberOfLines = 1;
        errorTipLabel.font = [UIFont systemFontOfSize:16];
        errorTipLabel.textAlignment = NSTextAlignmentCenter;
        errorTipLabel.textColor = [UIColor darkGrayColor];
        errorTipLabel.text = @"杜文全提醒：您的网络在开小差哦~";
        _errorTipLabel = errorTipLabel;
        [self addSubview:_errorTipLabel];
        
        UIButton* reloadButton = [UIButton buttonWithType:UIButtonTypeCustom];
        reloadButton.layer.masksToBounds = YES;
        reloadButton.layer.cornerRadius = 20;
        [reloadButton setTitle:@"  点击刷新" forState:UIControlStateNormal];
        reloadButton.titleLabel.font =[UIFont systemFontOfSize:15];
        [reloadButton setImage:[UIImage imageNamed:@"DWQupdate" ] forState:UIControlStateNormal];
        reloadButton.backgroundColor = [UIColor lightGrayColor];
        [reloadButton addTarget:self action:@selector(_clickReloadButton:) forControlEvents:UIControlEventTouchUpInside];
        _reloadButton = reloadButton;
        [self addSubview:_reloadButton];
        
        [_errorImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(self);
            make.centerY.equalTo(self.mas_centerY).offset(-30);
        }];
        
        [_errorTipLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.equalTo(self);
            make.height.equalTo(@20);
            make.top.equalTo(_errorImageView.mas_bottom);
        }];
        
        [_reloadButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.width.mas_equalTo(LSCREENW-60);
            make.height.mas_equalTo(40);
            make.centerX.equalTo(self);
            make.bottom.equalTo(self.mas_bottom).offset(-30);
        }];
    }
    return self;
}

```

- 3.点击按钮刷新的实现，也是通过Runtime动态添加block属性来实现

```onjective-c
- (DWQErrorPageView *)errorPageView{
    return objc_getAssociatedObject(self, _cmd);
}

- (void)configReloadAction:(void (^)())block{
    self.reloadAction = block;
    if (self.errorPageView && self.reloadAction) {
        self.errorPageView.didClickReloadBlock = self.reloadAction;
    }
}
```

##使用方法
一行代码即可调用，代码示例如下：

```objective-c
//        //如果无网络
//        [self.view showErrorPageView];
//        [self.view configReloadAction:^{
//            NSLog(@"点击我就可以刷新了啊");
//        }];
    
         //空数据
           [self.view showBlankPageView];
        //隐藏
        //[self.view hideBlankPageView];
```
##效果图展示：


![效果展示.jpg](http://upload-images.jianshu.io/upload_images/2231137-d0e442ecf70e9956.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/300)



##控件下载地址

[DWQEmptyView](https://github.com/DevelopmentEngineer-DWQ/DWQEmptyView)

觉得不错的小伙伴给个赞，在GitHub上给个Star噢！！！~~~~
