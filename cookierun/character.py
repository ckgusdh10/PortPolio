from pico2d import *


class Character:
    image_init = None
    state_init = None
    collidtime = 0
    score = 0
    def __init__(self):
        self.x = 100
        self.y = 240
        self.frame = 1
        self.state = "run"
        self.jump_state = "up"
        self.slide_count = 0
        self.hp = 500
        self.score = 0


        if self.image_init == None:
            self.run = load_image('image\\cookie_run.png')
            self.jump = load_image('image\\cookie_run_jump.png')
            self.slide = load_image('image\\cookie_run_slide.png')
            self.collid = load_image('image\\cookie_run_collid.png')
            self.hpbar = load_image('image\\hp.png')

        if self.state_init == None:
            self.jump_sound = load_wav('Sound\\jump.wav')
            self.jump_sound.set_volume(64)
            self.slide_sound = load_wav('Sound\\slide.wav')
            self.slide_sound.set_volume(64)
            self.collid_sound = load_wav('Sound\\collid.wav')
            self.collid_sound.set_volume(64)

    def heal(self):
        self.hp += 100



    def get_score(self):
        return self.score

    def update(self):
        self.hp -= 1

        self.frame += 1
        if self.frame == 6:
            self.frame = 1

        if self.state == "collid":

            self.collidtime += 1
            if self.collidtime == 1:
                self.collid_sound.play()
                self.hp -= 50
            if(self.collidtime >= 10):


                self.state = "run"
                self.y = 240
                self.collidtime = 0

        if self.state == "jump" and self.jump_state == "up":
            if self.y >= 350:
                self.jump_state = "down"
            self.y += 15

        if self.state == "jump" and self.jump_state == "down":
            if self.y >= 250:
                self.y -= 15

        if self.state == "jump" and self.y == 240:
            self.state = "run"
            self.jump_state = "up"

        if self.state == "slide":
            self.y = 220

    def get_bb(self):
        return self.x - 30, self.y - 40, self.x + 25, self.y + 35

    def draw_bb(self):
        draw_rectangle(*self.get_bb())


    def draw(self):
        if self.state == "run":
            self.run.clip_draw(self.frame * 75, 0, 75, 87, self.x, self.y)
        elif self.state == "jump":
            self.jump.draw(self.x, self.y)
        elif self.state == "slide":
            self.slide.draw(self.x, self.y)
        elif self.state == "collid":
            self.collid.draw(self.x, self.y)
        self.hpbar.draw_to_origin(0, 500, self.hp, 50)



