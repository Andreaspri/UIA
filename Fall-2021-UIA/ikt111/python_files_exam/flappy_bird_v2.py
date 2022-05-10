from random import randint, sample
import ikt111_games

game = ikt111_games.Flappy()

NUMBER_OF_PARENTS = 50
MUTATION_CHANCE = 2



def generate_next_generation(birds):
    # Sorting the birds based on their fitness
    sorted(birds, key=lambda x: x.fitness)
    # Taking the best birds as parents for the next generation
    parents = birds[:NUMBER_OF_PARENTS]
    new_birds = []
    for p in range(int((100 - len(parents)) / 2)):
        if len(parents) == 2:
            parent_1 = parents.pop(0)
            parent_2 = parents.pop(0)
        else:
            random_parents = sample(range(0, len(parents) - 1), 2)
            parent_1 = parents.pop(random_parents[0])
            parent_2 = parents.pop(random_parents[1])
        # Making new children
        child_1 = ikt111_games.flappy.Bird()
        child_2 = ikt111_games.flappy.Bird()
        for i in range(0, len(parent_1.genes)):
            # Making it a 50/50 chance to get the chromosome from parent1 or parent2
            if randint(0, 1) == 1:
                child_1.genes[i] = parent_1.genes[i]
                child_2.genes[i] = parent_2.genes[i]
            else:
                child_1.genes[i] = parent_2.genes[i]
                child_2.genes[i] = parent_1.genes[i]

            # Making the mutations
            if randint(0, 100) <= MUTATION_CHANCE:
                child_1.genes[i] = [randint(-4, 4), randint(-4, 4)]
            if randint(0, 100) <= MUTATION_CHANCE:
                child_2.genes[i] = [randint(-4, 4), randint(-4, 4)]

        # Adding the birds to he next generation
        new_birds.append(child_1)
        new_birds.append(child_2)
        new_birds.append(parent_1)
        new_birds.append(parent_2)


    print(len(new_birds))
    return new_birds

@game.register_ai
def super_ai(birds):
    birds = generate_next_generation(birds)
    return birds


game.start(1000)
