from pico2d import *
import random
import json

jelly_data_file = open('MapData\\jelly', 'r')
jelly_data = json.load(jelly_data_file)
jelly_data_file.close()

hp_data_file = open('MapData\\hp', 'r')
hp_data = json.load(hp_data_file)
hp_data_file.close()

################################################

jelly_data_file2 = open('MapData\\jelly2', 'r')
jelly_data2 = json.load(jelly_data_file2)
jelly_data_file2.close()

hp_data_file2 = open('MapData\\hp2', 'r')
hp_data2 = json.load(hp_data_file2)
hp_data_file2.close()


class Jelly:
    global jelly_data
    image = None
    jellyitem = None
    state = "None"
    PIXEL_PER_METER = (10.0 / 0.3)
    RUN_SPEED_KMPH = 20.0
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    def __init__(self):
        self.speed = 10
        self.distance = 0

        if Jelly.image == None:
            self.jelly = load_image('image\\jelly.png')
        if self.jellyitem == None:
            self.jellyitem_sound = load_wav('Sound\\jelly.wav')
            self.jellyitem_sound.set_volume(64)

    def jellysound(self):
        self.jellyitem_sound.play()

    def create(self):
        hurdle_state = {
            "jelly": self.image
        }
        jelly = []
        for name in jelly_data:
            jel = Jelly()
            jel.name = name
            jel.x = jelly_data[name]['x']
            jel.y = jelly_data[name]['y']
            jel.state = hurdle_state[jelly_data[name]['state']]
            jelly.append(jel)

        return jelly

    def update(self, frame_time):
        if Jelly.RUN_SPEED_PPS * frame_time > 7:
            self.distance = 10
        else:
            self.distance = Jelly.RUN_SPEED_PPS * frame_time

        self.x -= self.distance

    def get_bb(self):
        return self.x - 20, self.y - 20, self.x + 15, self.y + 15

    def draw_bb(self):
        draw_rectangle(*self.get_bb())

    def draw(self):
        self.jelly.draw(self.x, self.y)

class Hp:
    global hp_data
    image = None
    hpitem = None
    state = "None"
    PIXEL_PER_METER = (10.0 / 0.3)
    RUN_SPEED_KMPH = 20.0
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    def __init__(self):
        self.speed = 10
        self.distance = 0

        if Hp.image == None:
            self.hp = load_image('image\\hp_jelly.png')

        if self.hpitem == None:
            self.hpitem_sound = load_wav('Sound\\hp_jelly.wav')
            self.hpitem_sound.set_volume(64)

    def create(self):
        hurdle_state = {
            "hp": self.image
        }
        hp = []
        for name in hp_data:
            hpj = Hp()
            hpj.name = name
            hpj.x = hp_data[name]['x']
            hpj.y = hp_data[name]['y']
            hpj.state = hurdle_state[hp_data[name]['state']]
            hp.append(hpj)

        return hp

    def update(self, frame_time):
        if Jelly.RUN_SPEED_PPS * frame_time > 7:
            self.distance = 10
        else:
            self.distance = Jelly.RUN_SPEED_PPS * frame_time

        self.x -= self.distance

    def get_bb(self):
        return self.x - 20, self.y - 20, self.x + 15, self.y + 15

    def draw_bb(self):
        draw_rectangle(*self.get_bb())

    def draw(self):
        self.hp.draw(self.x, self.y)


class Jelly2:
    global jelly_data2
    image = None
    jellyitem = None
    state = "None"
    PIXEL_PER_METER = (10.0 / 0.3)
    RUN_SPEED_KMPH = 20.0
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    def __init__(self):
        self.speed = 10
        self.distance = 0

        if Jelly2.image == None:
            self.jelly = load_image('image\\jelly.png')
        if self.jellyitem == None:
            self.jellyitem_sound = load_wav('Sound\\jelly.wav')
            self.jellyitem_sound.set_volume(64)

    def jellysound(self):
        self.jellyitem_sound.play()

    def create(self):
        hurdle_state = {
            "jelly": self.image
        }
        jelly = []
        for name in jelly_data2:
            jel = Jelly2()
            jel.name = name
            jel.x = jelly_data2[name]['x']
            jel.y = jelly_data2[name]['y']
            jel.state = hurdle_state[jelly_data2[name]['state']]
            jelly.append(jel)

        return jelly

    def update(self, frame_time):
        if Jelly2.RUN_SPEED_PPS * frame_time > 7:
            self.distance = 10
        else:
            self.distance = Jelly2.RUN_SPEED_PPS * frame_time

        self.x -= self.distance

    def get_bb(self):
        return self.x - 20, self.y - 20, self.x + 15, self.y + 15

    def draw_bb(self):
        draw_rectangle(*self.get_bb())

    def draw(self):
        self.jelly.draw(self.x, self.y)


class Hp2:
    global hp_data2
    image = None
    hpitem = None
    state = "None"
    PIXEL_PER_METER = (10.0 / 0.3)
    RUN_SPEED_KMPH = 20.0
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    def __init__(self):
        self.speed = 10
        self.distance = 0

        if Hp2.image == None:
            self.hp2 = load_image('image\\hp_jelly.png')

        if self.hpitem == None:
            self.hpitem_sound = load_wav('Sound\\hp_jelly.wav')
            self.hpitem_sound.set_volume(64)

    def create(self):
        hurdle_state = {
            "hp": self.image
        }
        hp = []
        for name in hp_data2:
            hpj = Hp2()
            hpj.name = name
            hpj.x = hp_data2[name]['x']
            hpj.y = hp_data2[name]['y']
            hpj.state = hurdle_state[hp_data2[name]['state']]
            hp.append(hpj)

        return hp

    def update(self, frame_time):
        if Jelly.RUN_SPEED_PPS * frame_time > 7:
            self.distance = 10
        else:
            self.distance = Jelly2.RUN_SPEED_PPS * frame_time

        self.x -= self.distance

    def get_bb(self):
        return self.x - 20, self.y - 20, self.x + 15, self.y + 15

    def draw_bb(self):
        draw_rectangle(*self.get_bb())

    def draw(self):
        self.hp2.draw(self.x, self.y)