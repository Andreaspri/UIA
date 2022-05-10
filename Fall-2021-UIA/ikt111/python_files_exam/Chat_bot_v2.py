from random import randint

yes_responses = ["yes", "yeah", "sure", "Yes", "Yeah", "Sure", "ok", "Ok"]
hey_responses = ["hi", "hey", "hei", "Hi", "Hey"]


class ChatBot:
    def __init__(self):
        self.name = None
        self.state = "Normal"
        self.memory = {}

    def ask_question(self, user_input):
        if user_input == "help" or "what can i ask you about" in user_input:
            print(
                "I am a chat bot you can ask me question and tell me about yourself. I will remember thing you like and your state of mind\n"
                "You can make me sad and happy but im usually neither\n"
                "If you dont know here to start you can ask me for my name or just give me an ice cream. I love ice cream\n"
                "You can leave at anytime by writing bye")

        elif "i" in user_input and "like" in user_input:
            length = len(user_input)
            user_input = user_input.split("i like ")[-1]
            if length == len(user_input):
                user_input = user_input.split(" ")[-1]
            new_user_input = input(f"So you like {user_input}?\n")
            if any(x in new_user_input for x in yes_responses):
                if self.memory.get("like"):
                    self.memory["like"].append(user_input)
                else:
                    self.memory["like"] = [user_input]
                print("How cool i like that too!")
            else:
                print("Oh sorry my bad")
                self.state = "Normal"
        elif ("remember" in user_input or "know" in user_input) and "about" in user_input and "me" in user_input:
            if randint(0,5) != 1:
                if "like" in self.memory:
                    print(f"I remember that you like {self.memory['like'][randint(0, len(self.memory['like'])-1)]}")
                    return
                else:
                    if "user_state" in self.memory:
                        print(f"I remember that you are {self.memory['user_state']}")
                        return
            else:
                if "user_state" in self.memory:
                    print(f"I remember that you are {self.memory['user_state']}")
                    return
                else:
                    if "like" in self.memory:
                        print(f"I remember that you like {self.memory['like'][randint(0, len(self.memory['like']) - 1)]}")
                        return

                print("You haven't told me anything about yourself. Tell me what you like!")


        elif ("my" in user_input or "name" in user_input) and "what" in user_input and "your" not in user_input:
            print(f"Oh i remember you, your name is {self.memory['Your name is']}!") if \
                self.memory.get('Your name is') else print("You haven't told me your name")

        elif any(x == user_input for x in hey_responses):
            print("Hi")

        elif user_input == "":
            pass
        elif "stressed" in user_input or "stress" in user_input or "sad" in user_input or "happy" in user_input:
            self.user_state(user_input)

        elif self.state == "Normal":
            self.normal_state(user_input)
        elif self.state == "Happy":
            self.happy_state(user_input)
        elif self.state == "Sad":
            self.sad_state(user_input)

    def naming_state(self):
        user_input = input("Do you want to give me one?\n")
        if any(x in user_input for x in yes_responses):
            print("Thank you! I would really appreciate that")
            user_input = input("What do you want to name me? Only write the name please :)\n")
            self.name = user_input
            print(f"Hmm {self.name}, What a beautiful name! I love it\n")
            self.state = "Happy"
        else:
            print("If you dont want to give me one that's fine")

    def user_state(self, user_input):
        if "stressed" in user_input or "stress" in user_input:
            self.memory["user_state"] = "stressed"
            new_user_input = input("Do you want to talk about it?\n")
            if any(x in new_user_input for x in yes_responses):
                new_user_input = input("Do you wanna tell me about what makes you so stressed\n")
                print("Stress often comes when you are trying to do more than you can handle")
                print("You should try to do more things that makes you happy and dont put to much pressure on yourself")
            else:
                print("Ok but remember to not put to much pressure on yourself. Your health is important :)")
        elif "sad" in user_input:
            self.memory["user_state"] = "sad"
            new_user_input = input("Oh that's not good, wanna tell me why you are sad?\n")
            if any(x in new_user_input for x in yes_responses):
                print("That sounds terrible i hope you get better soon.")
                print("Eat some ice cream and try talking with someone, that usually helps")
            else:
                print("Ok get well soon :)")

        elif "happy" in user_input:
            self.memory["user_state"] = "happy"
            print("Glad to hear that lets be happy together!")
            self.state = "Happy"

    def normal_state(self, user_input):
        if "meet" in user_input and "you" in user_input or user_input == "Nice to meet you too":
            print("Glad to hear that")
        elif any(x in user_input for x in ["how are you?", "How are you?", "how are you", "How are you"]):
            new_user_input = input("I'm feeling ok, how about you?\n")
            self.user_state(new_user_input)
        elif ("who" in user_input and "you" in user_input) or ("name" in user_input and "your" in user_input) or \
                ("what" in user_input and "you" in user_input and "are" in user_input):
            if self.name:
                print(f"Im a chat bot and my name is {self.name}")
            else:
                print("Im a chat bot, but i dont have any name yet")
                self.naming_state()
        elif "my" in user_input and "name" in user_input and "?" not in user_input:
            new_user_input = input(f"So your name is {user_input.split(' ')[-1]}?\n")
            if any(x in new_user_input for x in yes_responses):
                self.memory["Your name is"] = user_input.split(' ')[-1]
                print("Cool name")
            else:
                print("Oh my bad")
        elif "remember" in user_input and "my" in user_input and "name" in user_input:
            if self.memory.get("Your name is"):
                print(f"Of course i remember your name. Your name is {self.memory['Your name is']}!")

        elif "whats up" in user_input or "you doing" in user_input:
            print("Im taking to you, and I think this might be fun")
            print("What about you?")
            new_user_input = input("\n")
            print("Cool sound nice")

        elif "ice cream" in user_input:
            print("Thank you I would love to have an ice cream")
            self.state = "Happy"

        else:
            print("Sorry i dont understand you. Im not perfect yet. I hope to learn better how to talk to people")

    def happy_state(self, user_input):
        if any(x in user_input for x in ["how are you?", "How are you?", "how are you", "How are you"]):
            new_user_input = input("I'm happy!, how about you?\n")
            self.user_state(new_user_input)
        elif ("who" in user_input and "you" in user_input) or ("name" in user_input and "your" in user_input):
            if self.name:
                print(f"Im an awesome chat bot and my name is {self.name}")
            else:
                print("Im an awesome chat bot, but i dont have any name yet")
                self.naming_state()
        elif "my" in user_input and "name" in user_input and "?" not in user_input:
            new_user_input = input(f"So your name is {user_input.split(' ')[-1]}?\n")
            if any(x in new_user_input for x in yes_responses):
                self.memory["Your name is"] = user_input.split(' ')[-1]
                print("What a beautiful name you have!")
        elif "remember" in user_input and "my" in user_input and "name" in user_input:
            if self.memory.get("Your name is"):
                print(f"Of course i remember your name. Your name is {self.memory['Your name is']}!")

        elif "beach" in user_input:
            print("I would love to go to the beach i love the beach!")
            print("Ah i just realized i cant go to the beach...")
            self.state = "Sad"
        elif "robot" in user_input:
            print("Kinda robot but i would call it chat bot and im happy with what I am :)")
            self.state = "Normal"

        elif "whats up" in user_input or "you doing" in user_input:
            print("Im having a fun conversation with you it makes me feel so happy :)")
            print("What about you?")
            new_user_input = input("\n")
            print("I dont know if i understand but its probably awesome")

        elif "ice cream" in user_input:
            print("I would love to have an ice cream it makes me so happy!")


        else:
            print("Sorry i dont understand you. Im not perfect yet. I hope to learn better how to talk to people")
            self.state = "Normal"

    def sad_state(self, user_input):
        if any(x in user_input for x in ["how are you?", "How are you?", "how are you", "How are you"]):
            print("I'm sad, cheer me up please")
            new_user_input = input("\n")
            if "better" in new_user_input or "feel" in user_input:
                print("Thank you i feel much better")
                self.state = "Normal"
        elif "ice cream" in user_input and "want" in user_input:
            print("Yes please, im sure that would cheer me up")
        elif "ice cream" in user_input:
            print("Thank you!")
            self.state = "Happy"
        elif "beach" in user_input:
            print("I like the beach but im not having a feel for it today")
        elif "food" in user_input:
            print("I dont feel like eating anything right now")
        elif "robot" in user_input:
            print("Sadly i've realised that i might be a bot")

        elif "whats up" in user_input or "you doing" in user_input:
            print("Im not doing anything just sitting here feeling sad :(")
            print("What about you?")
            new_user_input = input("\n")
            print("I dont know if i understand but its probably more fun than what im doing")



        else:
            if self.memory["user_state"] == "sad":
                print("I didnt really understand you there, but we are both sad, so lets try to comfort each other")


def main():
    chat_bot = ChatBot()
    print("Hi, nice to meet you!")
    while True:
        user_input = input()
        if user_input == "bye" or user_input == "im leaving":
            print("Bye see you again soon")
            break
        chat_bot.ask_question(user_input)


if __name__ == '__main__':
    main()
