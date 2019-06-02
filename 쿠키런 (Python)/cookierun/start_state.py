import game_framework
import title_state
from pico2d import *


name = "StartState"
image = None
dev = None
kakao = None
logo_time = 0.0


def enter():
    global image, dev, kakao, title
    image = load_image('image\\kpu_credit.png')
    dev = load_image('image\\title_CI.png')
    kakao = load_image('image\\title_kakao.png')

def exit():
    global image, dev, kakao
    del(image)
    del(dev)
    del(kakao)
    close_canvas()


def update():
    global logo_time

    if (logo_time > 3.0):
        logo_time = 0
        game_framework.push_state(title_state)
    delay(0.01)
    logo_time += 0.01

def draw():
    global image, dev, kakao
    clear_canvas()
    image.draw(400,300)
    if(logo_time > 1.0):
        dev.draw(400, 300)
    if(logo_time > 2.0):
        kakao.draw(400, 300)
    update_canvas()

def handle_events():
    events = get_events()
    pass


def pause(): pass

def resume(): pass




