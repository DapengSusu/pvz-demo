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

    // ??????????????????
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

    // ??????????????????
    auto back_btn = ui::Button::create(
        "res/images/Almanac_IndexButton.png",           // normal
        "res/images/Almanac_IndexButtonHighlight.png",  // selected
        ""                                              // disabled
    );

    // ??????????????????
    back_btn->setTitleText("BACK");
    // ??????????????????
    back_btn->setTitleFontName("fonts/arialbd.ttf");
    // log("\nfont name: %s", (back_btn->getTitleFontName()).c_str());
    // ??????????????????
    back_btn->setTitleFontSize(18.0f);
    // ??????????????????
    back_btn->setTitleColor(Color3B::BLACK);
    // ??????????????????????????????
    back_btn->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    // ??????????????????????????????0?????????
    back_btn->setZoomScale(0.1f);

    // ????????????
    back_btn->setAnchorPoint(Vec2(0, 0));
    // ????????????
    back_btn->setPosition(Vec2::ZERO);

    // ??????????????????
    back_btn->addClickEventListener([&](Ref* sender) {
        // ?????????main_scene
        Director::getInstance()->popScene();
    });

    // ????????????????????????
    this->addChild(back_btn, 1);
    ///////////////////////////////////////
    // // ?????????????????????
    // auto user_info_bar = Sprite::create("res/images/SelectorScreen_WoodSign1_32.png");

    // if (nullptr == user_info_bar) {
    //     problemLoading("'res/images/SelectorScreen_WoodSign1_32.png'");
    // } else {
    //     // ????????????
    //     user_info_bar->setAnchorPoint(Vec2(0.5, 0.5));

    //     // position the sprite on the center of the screen
    //     // ????????????
    //     auto size = user_info_bar->getContentSize();
    //     // log("size: (%.2f, %.2f)", size.width, size.height);
    //     user_info_bar->setPosition(Vec2(size.width/2 + 20, visible_size.height - size.height/2));

    //     // add the sprite as a child to this layer
    //     // ??????????????????
    //     this->addChild(user_info_bar, 1);
    // }

    return true;
}
