#include <keypadc.h>
#include <graphx.h>
#include <tice.h>
#include <game.h>

int main()
{
    gfx_Begin();
    init();
    gfx_SetColor(0);
    gfx_SetDrawBuffer();
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    unsigned long prev_time = timer_Get(1);
    Player *player = getPlayer();
    do {
        player->update();
        gfx_FillScreen(255);
        player->render();
        gfx_SwapDraw();
        while (timer_Get(1) < prev_time+300) {

        }
        prev_time = timer_Get(1);
    } while(!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyDel));
    if(!kb_IsDown(kb_KeyDel)) {
        save_game();
    }
    gfx_End();
    return 0;
}
