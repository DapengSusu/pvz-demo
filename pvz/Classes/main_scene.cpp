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

#include "main_scene.h"
#include "play_adventure_scene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

// on "init" you need to initialize your instance
bool MainScene::init()
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

    // 添加主场景
    // add "MainScene" splash screen"
    auto main_screen = Sprite::create("res/images/Surface.png");

    if (main_screen == nullptr) {
        problemLoading("'res/images/Surface.png'");
    } else {
        main_screen->setAnchorPoint(Vec2(0.5, 0.5));

        // position the sprite on the center of the screen
        main_screen->setPosition(Vec2(visible_size.width/2, visible_size.height/2));

        // add the sprite as a child to this layer
        this->addChild(main_screen, 0);
    }

    /////////////////////////////////////
    // 完善墓碑上的四个板块
    // creating a Menu from a Vector of items
    Vector<MenuItem *> menu_items;

    // 1、添加 “冒险模式”
    // 将整张图分别保存：normal, selected, disabled
    auto start_adventure_disabled_frame = SpriteFrame::create(
        "res/images/SelectorScreenStartAdventure_32.png",
        Rect(0, 0, 331, 290/2)
    );
    auto start_adventure_normal_frame = SpriteFrame::create(
        "res/images/SelectorScreenStartAdventure_32.png",
        Rect(0, 290/2, 331, 290/2)
    );
    auto start_adventure = MenuItemImage::create(
        "", // normal
        "", // selected
        "", // disabled
        [&](Ref* sender) {
            // log("start_adventure");
            // 创建游戏场景 play_adventure_scene
            auto play_adventure_scene = PlayAdventureScene::createScene();

            // 使用play_adventure_scene替换当前场景（main_scene）
            // Director::getInstance()->replaceScene(main_scene);
            Director::getInstance()->pushScene(play_adventure_scene);
        }
    );

    // 设置start_adventure三种显示状态
    start_adventure->setNormalSpriteFrame(start_adventure_normal_frame);
    start_adventure->setSelectedSpriteFrame(start_adventure_disabled_frame);
    start_adventure->setDisabledSpriteFrame(start_adventure_disabled_frame);

    // 2、添加 “迷你游戏”
    // 将整张图分别保存：normal, selected, disabled
    auto survival_disabled_frame = SpriteFrame::create(
        "res/images/SelectorScreenSurvival_32.png",
        Rect(0, 0, 313, 262/2)
    );
    auto survival_normal_frame = SpriteFrame::create(
        "res/images/SelectorScreenSurvival_32.png",
        Rect(0, 262/2, 313, 262/2)
    );
    auto survival = MenuItemImage::create(
        "", // normal
        "", // selected
        "", // disabled
        [&](Ref* sender) {
            log("survival");
        }
    );

    // 设置位置
    auto pos = start_adventure->getPosition();
    survival->setPosition(pos.x-10, pos.y-95);

    // 设置survival三种显示状态
    survival->setNormalSpriteFrame(survival_normal_frame);
    survival->setSelectedSpriteFrame(survival_disabled_frame);
    survival->setDisabledSpriteFrame(survival_disabled_frame);

    // 3、添加 “解密模式”
    // 将整张图分别保存：normal, selected, disabled
    auto riddle_disabled_frame = SpriteFrame::create(
        "res/images/SelectorScreenRiddle.png",
        Rect(0, 0, 286, 242/2)
    );
    auto riddle_normal_frame = SpriteFrame::create(
        "res/images/SelectorScreenRiddle.png",
        Rect(0, 242/2, 286, 242/2)
    );
    auto riddle = MenuItemImage::create(
        "", // normal
        "", // selected
        "", // disabled
        [&](Ref* sender) {
            log("riddle");
        }
    );

    // 设置位置
    pos = survival->getPosition();
    riddle->setPosition(pos.x-5, pos.y-85);

    // 设置riddle三种显示状态
    riddle->setNormalSpriteFrame(riddle_normal_frame);
    riddle->setSelectedSpriteFrame(riddle_disabled_frame);
    riddle->setDisabledSpriteFrame(riddle_disabled_frame);

    // 4、添加 “益智模式”
    // 将整张图分别保存：normal, selected, disabled
    auto challenge_disabled_frame = SpriteFrame::create(
        "res/images/SelectorScreenChallenges_32.png",
        Rect(0, 0, 260, 220/2)
    );
    auto challenge_normal_frame = SpriteFrame::create(
        "res/images/SelectorScreenChallenges_32.png",
        Rect(0, 220/2, 260, 220/2)
    );
    auto challenge = MenuItemImage::create(
        "", // normal
        "", // selected
        "", // disabled
        [&](Ref* sender) {
            log("challenge");
        }
    );

    // 设置位置
    pos = riddle->getPosition();
    challenge->setPosition(pos.x-5, pos.y-75);

    // 设置challenge三种显示状态
    challenge->setNormalSpriteFrame(challenge_normal_frame);
    challenge->setSelectedSpriteFrame(challenge_disabled_frame);
    challenge->setDisabledSpriteFrame(challenge_disabled_frame);

    // 添加至菜单中
    /* repeat for as many menu items as needed */
    menu_items.pushBack(start_adventure);
    menu_items.pushBack(survival);
    menu_items.pushBack(riddle);
    menu_items.pushBack(challenge);
    auto menu = Menu::createWithArray(menu_items);

    // 相关设置
    menu->setAnchorPoint(Vec2(0.5f, 0.0f));
    menu->setPosition(570, 470);
    this->addChild(menu, 1);

    ///////////////////////////////////////
    // 显示用户信息栏
    auto user_info_bar = Sprite::create("res/images/SelectorScreen_WoodSign1_32.png");

    if (nullptr == user_info_bar) {
        problemLoading("'res/images/SelectorScreen_WoodSign1_32.png'");
    } else {
        // 设置锚点
        user_info_bar->setAnchorPoint(Vec2(0.5, 0.5));

        // position the sprite on the center of the screen
        // 设置位置
        auto size = user_info_bar->getContentSize();
        // log("size: (%.2f, %.2f)", size.width, size.height);
        user_info_bar->setPosition(Vec2(size.width/2 + 20, visible_size.height - size.height/2));

        // add the sprite as a child to this layer
        // 添加到场景中
        this->addChild(user_info_bar, 1);
    }

    return true;
}
