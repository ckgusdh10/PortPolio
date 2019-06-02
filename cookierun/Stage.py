from pico2d import *

class Stage:
    image_init = None

    PIXEL_PER_METER = (10.0 / 0.08)
    RUN_SPEED_KMPH = 10.0
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    image_init = None

    def __init__(self):
        self.stage1_x = 400
        self.stage1_y = 400
        self.stage2_x = 1200
        self.stage2_y = 400
        self.speed = 5
        self.distance = 0
        self.count = 0

        if self.image_init == None:
            self.stage1 = load_image('image\\stage1-0.png')
            self.stage2 = load_image('image\\stage1-0.png')

    def update(self, frame_time):
        if Stage.RUN_SPEED_PPS * frame_time > 7:
            self.distance = 10
        else:
            self.distance = Stage.RUN_SPEED_PPS * frame_time

        self.stage1_x -= self.distance
        self.stage2_x -= self.distance

        if self.stage2_x < - 400:
            self.count += 1
            self.stage2_x = 1190

        if self.stage1_x < - 400:
            self.count += 1
            self.stage1_x = 1190

        if self.count >= 7:
            self.stage1_x = 400
            self.stage1_y = 400
            self.stage2_x = 400
            self.stage2_y = 400


    def draw(self):
        self.stage1.draw(self.stage1_x, self.stage1_y)
        self.stage2.draw(self.stage2_x, self.stage2_y)


class Stage2:
    image_init = None

    PIXEL_PER_METER = (10.0 / 0.08)
    RUN_SPEED_KMPH = 10.0
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    image_init = None

    def __init__(self):
        self.stage1_x = 400
        self.stage1_y = 400
        self.stage2_x = 1200
        self.stage2_y = 400
        self.speed = 5
        self.distance = 0
        self.count = 0

        if self.image_init == None:
            self.stage1 = load_image('image\\stage2-0.png')
            self.stage2 = load_image('image\\stage2-0.png')

    def update(self, frame_time):
        if Stage.RUN_SPEED_PPS * frame_time > 7:
            self.distance = 10
        else:
            self.distance = Stage.RUN_SPEED_PPS * frame_time

        self.stage1_x -= self.distance
        self.stage2_x -= self.distance

        if self.stage2_x < - 400:
            self.count += 1
            self.stage2_x = 1190

        if self.stage1_x < - 400:
            self.count += 1
            self.stage1_x = 1190

        if self.count >= 7:
            self.stage1_x = 400
            self.stage1_y = 400
            self.stage2_x = 400
            self.stage2_y = 400


    def draw(self):
        self.stage1.draw(self.stage1_x, self.stage1_y)
        self.stage2.draw(self.stage2_x, self.stage2_y)

