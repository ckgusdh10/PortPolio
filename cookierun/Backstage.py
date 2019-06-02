from pico2d import *

class BackStage:
    image_init = None
    ChangeState = None

    PIXEL_PER_METER = (10.0 / 0.3)
    RUN_SPEED_KMPH = 30.0
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    def __init__(self):
        self.stage1_x = 400
        self.stage1_y = 400
        self.stage2_x = 1200
        self.stage2_y = 400
        self.frame = 1
        self.speed = 5
        self.distance = 0
        self.count = 0


        if BackStage.image_init == None:
            self.stage1 = load_image('image\\stage1-1.png')
            self.stage2 = load_image('image\\stage1-1.png')
            self.stage3 = load_image('image\\stage1-rot.png')
            self.bgm = load_music('Sound\\stage1.mp3')
            self.bgm.set_volume(64)
            self.bgm.repeat_play()

        if BackStage.ChangeState == None:
            self.ChangeState_sound = load_wav('Sound\ChangeState.wav')
            self.ChangeState_sound.set_volume(64)

    def update(self, frame_time):
        if BackStage.RUN_SPEED_PPS * frame_time > 7:
            self.distance = 10
        else:
            self.distance = BackStage.RUN_SPEED_PPS * frame_time

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

            if self.frame == 8:
                self.frame = 8

            else:
                self.frame = (self.frame + 1) % 9



    def draw(self):
        if self.count >= 7:
            self.ChangeState_sound.play()
            self.stage3.clip_draw(self.frame * 800, 0, 800, 800, self.stage1_x, self.stage1_y)
            delay(0.05)
        else:
            self.stage1.draw(self.stage1_x, self.stage1_y)
            self.stage2.draw(self.stage2_x, self.stage2_y)


class BackStage2:
    image_init = None

    PIXEL_PER_METER = (10.0 / 0.3)
    RUN_SPEED_KMPH = 20.0
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    def __init__(self):
        self.stage1_x = 400
        self.stage1_y = 400
        self.stage2_x = 1200
        self.stage2_y = 400
        self.frame = 1
        self.speed = 5
        self.distance = 0
        self.count = 0


        if BackStage.image_init == None:
            self.stage1 = load_image('image\\stage2-1.png')
            self.stage2 = load_image('image\\stage2-1.png')
            self.bgm = load_music('Sound\\stage2.mp3')
            self.bgm.set_volume(64)
            self.bgm.repeat_play()

    def update(self, frame_time):
        if BackStage.RUN_SPEED_PPS * frame_time > 7:
            self.distance = 10
        else:
            self.distance = BackStage.RUN_SPEED_PPS * frame_time

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


    def draw(self):
        if self.count >= 7:
            self.stage1.draw(self.stage1_x, self.stage1_y)
        else:
            self.stage1.draw(self.stage1_x, self.stage1_y)
            self.stage2.draw(self.stage2_x, self.stage2_y)