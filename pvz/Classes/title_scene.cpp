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

#include "title_scene.h"
#include "ui/CocosGUI.h"
#include "main_scene.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    return TitleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

// on "init" you need to initialize your instance
bool TitleScene::init()
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
    // add "TitleScene" splash screen"
    // ??????cocos logo: res/images/cocos2d-logo.png
    auto title_screen = Sprite::create("res/images/cocos2d-logo.png");

    if (nullptr == title_screen) {
        problemLoading("'res/images/cocos2d-logo.png'");
    } else {
        // ????????????
        title_screen->setAnchorPoint(Vec2(0.5, 0.5));

        // ?????????????????????logo
        title_screen->setScale(2.0f);

        // position the sprite on the center of the screen
        // ????????????
        title_screen->setPosition(Vec2(visible_size.width/2, visible_size.height/2));

        // add the sprite as a child to this layer
        // ??????????????????
        this->addChild(title_screen, 0);
    }

    // ??????2???
    auto logo_delay = DelayTime::create(2.0f);

    // logo???????????????????????????load??????
    auto title_screen_start = CallFunc::create([=]() {
        // ????????????
        title_screen->setScale(1.0f);
    
        // 2s?????????logo???????????????
        title_screen->setTexture("res/images/titlescreen.jpg");

        // ?????????????????????????????????
        auto title_logo = Sprite::create("res/images/title_new.png");

        // ????????????
        title_logo->setAnchorPoint(Vec2(0.5, 0));

        if (nullptr == title_logo) {
            problemLoading("'res/images/title_new.png'");
        } else {
            // position the sprite on the center of the screen
            // ?????????????????????????????????
            auto pos = Vec2(visible_size.width/2, visible_size.height-(title_logo->getContentSize().height + 20));
            title_logo->setPosition(pos);

            // add the sprite as a child to this layer
            // ??????????????????
            this->addChild(title_logo, 1);
        }

        // ?????????????????????
        std::vector<std::string> load_bar_vec {
            "res/images/LoadBar_dirt.png",
            "res/images/LoadBar_grass.png",
            "res/images/SodRollCap.png"
        };
        auto load_bar_dirt = Sprite::create(load_bar_vec.at(0));
        auto load_bar_grass = Sprite::create(load_bar_vec.at(1));
        auto load_roll_cap = Sprite::create(load_bar_vec.at(2));
        // ??????load_bar_grass??????size
        auto original_size = Size();

        if (nullptr == load_bar_dirt) {
            problemLoading(load_bar_vec.at(0).c_str());
        } else if (nullptr == load_bar_grass) {
            problemLoading(load_bar_vec.at(1).c_str());
        } else if (nullptr == load_roll_cap) {
            problemLoading(load_bar_vec.at(2).c_str());
        } else {
            // ??????????????????
            original_size = Size(load_bar_grass->getContentSize().width, load_bar_grass->getContentSize().height);
            load_bar_grass->setTextureRect(Rect(0, 0, 0, original_size.height));

            // ????????????
            load_bar_dirt->setAnchorPoint(Vec2(0.5, 0));
            load_bar_grass->setAnchorPoint(Vec2(0, 0));
            load_roll_cap->setAnchorPoint(Vec2(0.5, 0.5));

            // position the sprite on the center of the screen
            // ????????????
            load_bar_dirt->setPosition(Vec2(visible_size.width/2, 20));
            load_bar_grass->setPosition(Vec2(load_bar_dirt->getPosition().x - load_bar_dirt->getContentSize().width/2, 60));
            load_roll_cap->setPosition(Vec2(load_bar_grass->getPosition().x, 60 + load_roll_cap->getContentSize().height/2));

            // add the sprite as a child to this layer
            // ??????????????????
            this->addChild(load_bar_dirt, 1);
            this->addChild(load_bar_grass, 1);
            this->addChild(load_roll_cap, 2);
        }

        // ???????????????
        double delay = 2.0f;
        auto move = MoveTo::create(delay, Vec2(load_bar_dirt->getPosition().x + 140, 70));
        auto scale = ScaleTo::create(delay, 0.3f);
        auto rotate = RotateBy::create(delay, 360.0f);
        auto spawn = Spawn::create(move, scale, rotate, nullptr);

        // ????????????????????????
        Vector<SpriteFrame *> anim_frames;
        const int frame_count = 20;
        anim_frames.reserve(frame_count);
        double step = load_bar_dirt->getContentSize().width / frame_count;
        auto h = load_bar_grass->getContentSize().height;

        for (auto i = 0; i != frame_count; ++i) {
            anim_frames.pushBack(SpriteFrame::create(load_bar_vec.at(1), Rect(0, 0, step * i, h)));
        }

        // create the animation out of the frames
        auto animation = Animation::createWithSpriteFrames(anim_frames, 0.1f);
        auto animate = Animate::create(animation);

        // run it and repeat it one time
        // ????????????
        load_bar_grass->runAction(Repeat::create(animate, 1));

        // auto move_start_cb = CallFunc::create([=]() {
        //     // TODO: load_bar_grass????????????
        // });
        auto move_end_cb = CallFunc::create([=]() {
            // ?????????????????????????????????load_roll_cap
            this->removeChild(load_roll_cap, true);
            // load_roll_cap->setVisible(false);
        
            // ??????load_bar_grass??????size
            load_bar_grass->setTextureRect(Rect(0, 0, original_size.width, original_size.height));
        });

        // ????????????????????????
        auto start_game_button_cb = CallFunc::create([=]() {
            auto start_btn = ui::Button::create(
                "res/images/LoadBar.png", // normal
                "",                       // selected
                ""                        // disabled
            );

            // // ??????xml??????
            // auto file_utils = FileUtils::getInstance();
            // file_utils->loadFilenameLookupDictionaryFromFile("res/text/text.xml");
            // // ??????xml????????????key??????value
            // auto text = file_utils->getNewFilename("start_game");
            // log("\ntext: %s", text.c_str());

            // // ??????????????????
            // // TODO: ?????????????????????????????????
            // // start_btn->setTitleText(text);
            // start_btn->setTitleText("Start Game");
            // // ??????????????????
            // start_btn->setTitleFontName("fonts/arialbd.ttf");
            // // log("\nfont name: %s", (start_btn->getTitleFontName()).c_str());
            // // ??????????????????
            // start_btn->setTitleFontSize(18.0f);
            // // ??????????????????
            // start_btn->setTitleColor(Color3B::BLACK);
            // // ??????????????????????????????
            // start_btn->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
            // ??????????????????????????????0?????????
            start_btn->setZoomScale(0.0f);

            // ????????????
            start_btn->setAnchorPoint(Vec2(0.5, 0));
            // ????????????
            start_btn->setPosition(load_bar_dirt->getPosition());

            // ??????????????????
            start_btn->addClickEventListener([&](Ref* sender) {
                // ?????????main_scene
                // ??????main scene
                // create a scene. it's an autorelease object
                auto main_scene = MainScene::createScene();

                // ??????main_scene?????????????????????title_scene???
                Director::getInstance()->replaceScene(main_scene);
            });

            // ????????????????????????
            this->addChild(start_btn, 2);

            // ????????????????????????
            this->removeChild(load_bar_dirt, true);
            this->removeChild(load_bar_grass, true);
        });

        // ????????????????????????
        load_roll_cap->runAction(Sequence::create(spawn, move_end_cb, start_game_button_cb, nullptr));
    });

    // 2s???logo???????????????????????????load??????
    title_screen->runAction(Sequence::create(logo_delay, title_screen_start, nullptr));

    return true;
}
