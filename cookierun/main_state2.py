import random
from pico2d import *
from Stage import *
from character import *
from Backstage import *
from Hurdle import *
from Jelly import *
from score import *

import game_framework
import title_state
import result

running = None
current_time = 0.0
stage = None
character = None
backstage = None
hurdle = None
hurdle2 = None
jelly = None
hp = None
jellysound = None
hpjellysound = None

name = "MainState"


def collid(a, b):
    left_a, bottom_a, right_a, top_a = a.get_bb()
    left_b, bottom_b, right_b, top_b = b.get_bb()

    if left_a > right_b: return False
    if right_a < left_b: return False
    if top_a < bottom_b: return False
    if bottom_a > top_b: return False

    return True


def enter():
    global stage, character, backstage, running, hurdle, hurdle2, jelly, hp, jellysound, hpjellysound, font, score
    backstage = BackStage2()
    stage = Stage2()
    character = Character()
    hurdle = Hurdle2().create()
    hurdle2 = Hurdle22().create()
    jelly = Jelly2().create()
    hp = Hp2().create()
    jellysound = Jelly()
    hpjellysound = Hp()
    score = Score()
    running = True
    font = load_font('image\\ENCR10B.TTF')

def get_frame_time():
    global current_time

    frame_time = get_time() - current_time
    current_time += frame_time
    return frame_time


def exit():
    global stage, character, backstage, running, hurdle, hurdle2, jelly, hp
    del (stage)
    del (character)
    del (backstage)
    for hur in hurdle:
        hurdle.remove(hur)
        del (hur)
    del (hurdle)

    for hur in hurdle2:
        hurdle2.remove(hur)
        del (hur)
    del (hurdle2)

    for jel in jelly:
        jelly.remove(jel)
        del (jel)
    del (jelly)

    for hpj in hp:
        hp.remove(hpj)
        del(hpj)
    del(hp)


def pause():
    pass


def resume():
    pass


def update():
    global running, backstage, character, stage, hurdle, ascore, score

    handle_events()
    frame_time = get_frame_time()
    backstage.update(frame_time)
    character.update()
    stage.update(frame_time)
    score.stage2_score()
    ascore = score.score

    for hur in hurdle:
        hur.update(frame_time)
        if collid(character, hur):
            character.state = "collid"

    for hur in hurdle2:
        hur.update(frame_time)
        if collid(character, hur):
            character.state = "collid"

    for jel in jelly:
        jel.update(frame_time)
        if collid(character, jel):
            jellysound.jellyitem_sound.play()
            score.score += 100
            jelly.remove(jel)

    for hpj in hp:
        hpj.update(frame_time)
        if collid(character, hpj):
            hpjellysound.hpitem_sound.play()
            hp.remove(hpj)
            character.heal()

    if character.hp <= 0:
        game_framework.change_state(result)

def handle_events():
    global running

    if backstage.frame >= 8:
        #backstage.ChangeState_sound.play()
        game_framework.change_state(result)

    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            running = False
            # elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
            #   running = False
        else:

            if event.type == SDL_KEYDOWN and event.key == SDLK_z:
                character.jump_sound.play()
                character.state = "jump"
            elif event.type == SDL_KEYDOWN and event.key == SDLK_x:
                character.slide_sound.play()
                character.state = "slide"
            elif event.type == SDL_KEYUP and event.key == SDLK_x:
                character.state = "run"
                character.y = 240
            elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
                game_framework.change_state(title_state)
            elif event.type == SDL_KEYDOWN and event.key == SDLK_3:
                game_framework.change_state(result)


def draw():
    global backstage, stage, character, running
    clear_canvas()
    backstage.draw()


    #character.draw_bb()

    for hur in hurdle:
        hur.draw()
#        hur.draw_bb()

    for hur in hurdle2:
        hur.draw()
 #       hur.draw_bb()

    for jel in jelly:
        jel.draw()
  #      jel.draw_bb()

    for hpj in hp:
        hpj.draw()
   #     hpj.draw_bb()

    character.draw()
    font.draw(100, 550, 'Score : %3.2d' % score.score, (255, 255, 255))
    stage.draw()
    # for Hurdle1 in Hur:
    #   Hurdle1.draw()
    delay(0.04)
    update_canvas()

#    close_canvas()
