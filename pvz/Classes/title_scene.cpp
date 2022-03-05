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
    // 显示cocos logo: res/images/cocos2d-logo.png
    auto title_screen = Sprite::create("res/images/cocos2d-logo.png");

    if (nullptr == title_screen) {
        problemLoading("'res/images/cocos2d-logo.png'");
    } else {
        // 设置锚点
        title_screen->setAnchorPoint(Vec2(0.5, 0.5));

        // 设置缩放：放大logo
        title_screen->setScale(2.0f);

        // position the sprite on the center of the screen
        // 设置位置
        title_screen->setPosition(Vec2(visible_size.width/2, visible_size.height/2));

        // add the sprite as a child to this layer
        // 添加到场景中
        this->addChild(title_screen, 0);
    }

    // 显示2秒
    auto logo_delay = DelayTime::create(2.0f);

    // logo显示结束，开始加载load背景
    auto title_screen_start = CallFunc::create([=]() {
        // 缩放还原
        title_screen->setScale(1.0f);
    
        // 2s后替换logo显示新背景
        title_screen->setTexture("res/images/titlescreen.jpg");

        // 添加植物大战僵尸主标题
        auto title_logo = Sprite::create("res/images/title_new.png");

        // 设置锚点
        title_logo->setAnchorPoint(Vec2(0.5, 0));

        if (nullptr == title_logo) {
            problemLoading("'res/images/title_new.png'");
        } else {
            // position the sprite on the center of the screen
            // 设置位置：显示在正上方
            auto pos = Vec2(visible_size.width/2, visible_size.height-(title_logo->getContentSize().height + 20));
            title_logo->setPosition(pos);

            // add the sprite as a child to this layer
            // 添加到场景中
            this->addChild(title_logo, 1);
        }

        // 添加进度加载条
        std::vector<std::string> load_bar_vec {
            "res/images/LoadBar_dirt.png",
            "res/images/LoadBar_grass.png",
            "res/images/SodRollCap.png"
        };
        auto load_bar_dirt = Sprite::create(load_bar_vec.at(0));
        auto load_bar_grass = Sprite::create(load_bar_vec.at(1));
        auto load_roll_cap = Sprite::create(load_bar_vec.at(2));
        // 记录load_bar_grass初始size
        auto original_size = Size();

        if (nullptr == load_bar_dirt) {
            problemLoading(load_bar_vec.at(0).c_str());
        } else if (nullptr == load_bar_grass) {
            problemLoading(load_bar_vec.at(1).c_str());
        } else if (nullptr == load_roll_cap) {
            problemLoading(load_bar_vec.at(2).c_str());
        } else {
            // 设置初始显示
            original_size = Size(load_bar_grass->getContentSize().width, load_bar_grass->getContentSize().height);
            load_bar_grass->setTextureRect(Rect(0, 0, 0, original_size.height));

            // 设置锚点
            load_bar_dirt->setAnchorPoint(Vec2(0.5, 0));
            load_bar_grass->setAnchorPoint(Vec2(0, 0));
            load_roll_cap->setAnchorPoint(Vec2(0.5, 0.5));

            // position the sprite on the center of the screen
            // 设置位置
            load_bar_dirt->setPosition(Vec2(visible_size.width/2, 20));
            load_bar_grass->setPosition(Vec2(load_bar_dirt->getPosition().x - load_bar_dirt->getContentSize().width/2, 60));
            load_roll_cap->setPosition(Vec2(load_bar_grass->getPosition().x, 60 + load_roll_cap->getContentSize().height/2));

            // add the sprite as a child to this layer
            // 添加到场景中
            this->addChild(load_bar_dirt, 1);
            this->addChild(load_bar_grass, 1);
            this->addChild(load_roll_cap, 2);
        }

        // 进度条动画
        double delay = 2.0f;
        auto move = MoveTo::create(delay, Vec2(load_bar_dirt->getPosition().x + 140, 70));
        auto scale = ScaleTo::create(delay, 0.3f);
        auto rotate = RotateBy::create(delay, 360.0f);
        auto spawn = Spawn::create(move, scale, rotate, nullptr);

        // 创建进度条帧动画
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
        // 重复一次
        load_bar_grass->runAction(Repeat::create(animate, 1));

        // auto move_start_cb = CallFunc::create([=]() {
        //     // TODO: load_bar_grass逐渐延伸
        // });
        auto move_end_cb = CallFunc::create([=]() {
            // 动画结束，隐藏（删除）load_roll_cap
            this->removeChild(load_roll_cap, true);
            // load_roll_cap->setVisible(false);
        
            // 还原load_bar_grass初始size
            load_bar_grass->setTextureRect(Rect(0, 0, original_size.width, original_size.height));
        });

        // 创建开始游戏按钮
        auto start_game_button_cb = CallFunc::create([=]() {
            auto start_btn = ui::Button::create(
                "res/images/LoadBar.png", // normal
                "",                       // selected
                ""                        // disabled
            );

            // // 加载xml文件
            // auto file_utils = FileUtils::getInstance();
            // file_utils->loadFilenameLookupDictionaryFromFile("res/text/text.xml");
            // // 通过xml文件中的key获取value
            // auto text = file_utils->getNewFilename("start_game");
            // log("\ntext: %s", text.c_str());

            // // 设置按钮文字
            // // TODO: 设置按钮字体显示为中文
            // // start_btn->setTitleText(text);
            // start_btn->setTitleText("Start Game");
            // // 设置字体类型
            // start_btn->setTitleFontName("fonts/arialbd.ttf");
            // // log("\nfont name: %s", (start_btn->getTitleFontName()).c_str());
            // // 设置文字大小
            // start_btn->setTitleFontSize(18.0f);
            // // 设置文字颜色
            // start_btn->setTitleColor(Color3B::BLACK);
            // // 设置字体水平垂直居中
            // start_btn->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
            // 设置按钮点击缩放，为0不缩放
            start_btn->setZoomScale(0.0f);

            // 设置锚点
            start_btn->setAnchorPoint(Vec2(0.5, 0));
            // 设置位置
            start_btn->setPosition(load_bar_dirt->getPosition());

            // 设置点击事件
            start_btn->addClickEventListener([&](Ref* sender) {
                // 切换到main_scene
                // 创建main scene
                // create a scene. it's an autorelease object
                auto main_scene = MainScene::createScene();

                // 使用main_scene替换当前场景（title_scene）
                Director::getInstance()->replaceScene(main_scene);
            });

            // 添加按钮到场景中
            this->addChild(start_btn, 2);

            // 去掉被覆盖的元素
            this->removeChild(load_bar_dirt, true);
            this->removeChild(load_bar_grass, true);
        });

        // 开始播放加载动画
        load_roll_cap->runAction(Sequence::create(spawn, move_end_cb, start_game_button_cb, nullptr));
    });

    // 2s后logo显示结束，切屏显示load界面
    title_screen->runAction(Sequence::create(logo_delay, title_screen_start, nullptr));

    return true;
}
