/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "play_adventure_scene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* PlayAdventureScene::createScene()
{
    return PlayAdventureScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

// on "init" you need to initialize your instance
bool PlayAdventureScene::init()
{
    //////////////////////////////
    // super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visible_size = Director::getInstance()->getVisibleSize();
    // Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // debug info
    // log("visible_size: (%.2f, %.2f)", visible_size.width, visible_size.height);
    // log("origin: (%.2f, %.2f)", origin.x, origin.y);

    /////////////////////////////
    // add your codes below...

    // 添加游戏场景
    // add "PlayAdventureScene" splash screen"
    auto main_screen = Sprite::create("res/images/background1unsodded.jpg");

    if (main_screen == nullptr) {
        problemLoading("'res/images/background1unsodded.jpg'");
    } else {
        main_screen->setAnchorPoint(Vec2(0.5, 0.5));

        // position the sprite on the center of the screen
        main_screen->setPosition(Vec2(visible_size.width/2, visible_size.height/2));

        // add the sprite as a child to this layer
        this->addChild(main_screen, 0);
    }

    // 显示调试按钮
    auto back_btn = ui::Button::create(
        "res/images/Almanac_IndexButton.png",           // normal
        "res/images/Almanac_IndexButtonHighlight.png",  // selected
        ""                                              // disabled
    );

    // 设置按钮文字
    back_btn->setTitleText("BACK");
    // 设置字体类型
    back_btn->setTitleFontName("fonts/arialbd.ttf");
    // log("\nfont name: %s", (back_btn->getTitleFontName()).c_str());
    // 设置文字大小
    back_btn->setTitleFontSize(18.0f);
    // 设置文字颜色
    back_btn->setTitleColor(Color3B::BLACK);
    // 设置字体水平垂直居中
    back_btn->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    // 设置按钮点击缩放，为0不缩放
    back_btn->setZoomScale(0.1f);

    // 设置锚点
    back_btn->setAnchorPoint(Vec2(0, 0));
    // 设置位置
    back_btn->setPosition(Vec2::ZERO);

    // 设置点击事件
    back_btn->addClickEventListener([&](Ref* sender) {
        // 切换到main_scene
        Director::getInstance()->popScene();
    });

    // 添加按钮到场景中
    this->addChild(back_btn, 1);
    ///////////////////////////////////////
    // // 显示用户信息栏
    // auto user_info_bar = Sprite::create("res/images/SelectorScreen_WoodSign1_32.png");

    // if (nullptr == user_info_bar) {
    //     problemLoading("'res/images/SelectorScreen_WoodSign1_32.png'");
    // } else {
    //     // 设置锚点
    //     user_info_bar->setAnchorPoint(Vec2(0.5, 0.5));

    //     // position the sprite on the center of the screen
    //     // 设置位置
    //     auto size = user_info_bar->getContentSize();
    //     // log("size: (%.2f, %.2f)", size.width, size.height);
    //     user_info_bar->setPosition(Vec2(size.width/2 + 20, visible_size.height - size.height/2));

    //     // add the sprite as a child to this layer
    //     // 添加到场景中
    //     this->addChild(user_info_bar, 1);
    // }

    return true;
}
