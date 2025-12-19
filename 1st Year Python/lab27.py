from random import randint
outputs = ["It is certain.",
"It is decidedly so.",
"Without a doubt.",
"Yes definitely.",
"You may rely on it.",
"As I see it, yes.",
"Most likely.",
"Outlook good.",
"Yes.",
"Signs point to yes.",
"Reply hazy, try again.",
"Ask again later.",
"Better not tell you now.",
"Cannot predict now.",
"Concentrate and ask again.",
"Don't count on it.",
"My reply is no.",
"My sources say no.",
"Outlook not so good.",
"Very doubtful."]


question = input("Im the magic 8 ball, ask me a yes/no question: ")


print(f'{outputs[randint(0,len(outputs))]}')

done = False
while not done:
    question = question.lower()
    if question == 'done':
        done = True
        print("Have a good day!")
    elif question != 'done':
        question = input("What is your next quesiton?: ")
        print(f'{outputs[randint(0,len(outputs))]}')