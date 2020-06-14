#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct pokemon {char *name; int number; int health;};

struct pokemon create(int r) {
	struct pokemon p;
	p.number = r % 9 + 1;

	switch (p.number) {
		case 1:
			p.name = "bulbasaur";
			break;
		case 2:
			p.name = "ivysaur";
			break;
		case 3:
			p.name = "venusaur";
			break;
		case 4:
			p.name = "charmander";
			break;
		case 5:
			p.name = "charmeleon";
			break;
		case 6:
			p.name = "charizard";
			break;
		case 7:
			p.name = "squirtle";
			break;
		case 8:
			p.name = "wartortle";
			break;
		case 9:
			p.name = "blastoise";
			break;
	}

	p.health = 20;
	return p;
}

void pokemon_print(struct pokemon p)
{
	printf("your Pokemon is named: %s \nits number is: %d \nits health is: %d\n", p.name, p.number, p.health);
}

void nickname(struct pokemon *p, char *nickname)
{
	p->name = nickname;
}

void heal(struct pokemon *p, int food)
{
	p->health += food;
}

int main()
{
	//random #
	srand(time(NULL));

	int r = rand();
	struct pokemon p = create(r);
	r = rand();
	struct pokemon p1 = create(r);
	r = rand();
	struct pokemon p2 = create(r);

	printf("		TESTING NICKNAMING		\n");
	printf("p:\n");
	pokemon_print(p);
	printf("-- nicknaming p to \"doot\" --\n");
	nickname(&p, "doot");
	pokemon_print(p);

	printf("\np1:\n");
	pokemon_print(p1);
	printf("-- nicknaming p1 to \"hoot\" --\n");
	nickname(&p1, "hoot");
	pokemon_print(p1);

	printf("\n\n		TESTING HEALING		\n");
	printf("p:\n");
	pokemon_print(p);
	printf("-- healing p by 10 --\n");
	heal(&p, 10);
	pokemon_print(p);

	printf("\np1:\n");
	pokemon_print(p1);
	printf("-- healing p1 by 8 --\n");
	heal(&p1, 8);
	pokemon_print(p1);

	printf("\np2:\n");
	pokemon_print(p2);
	printf("-- healing p2 by 100 --\n");
	heal(&p2, 100);
	pokemon_print(p2);

	return 0;
}
