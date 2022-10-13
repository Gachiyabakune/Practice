#pragma once

struct E_SHOT
{
        bool flag;//弾が発射中かどうか
        double x;//x座標
        double y;//y座標

        int gh;//グラフィックハンドル

        int width, height;//画像の幅と高さ

        int pattern;//ショットパターン

        int speed;//弾スピード
 
};

#define ENEMY_SNUM 50
