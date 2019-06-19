#include "headers.h"
#include "engine.h"

/* #include <readline/readline.h> */
/* #include <readline/history.h> */

#include <termios.h> //provides functions describing a general terminal interface that provides control of asynchronous communication ports

/*
   termios structure

   tcflag_t c_iflag;       input modes
   tcflag_t c_oflag;       output modes
   tcflag_t c_cflag;       control modes
   tcflag_t c_lflag;       local modes
   cc_t     c_cc[NCCS];    special characters
   */

#define WRITE 1

static void sighandler(int signo)
{
	if (signo == SIGINT) {
		int f = fork();
		if (f) {
			int fstatus;
			waitpid(f, &fstatus, 0);
			if (WIFEXITED(fstatus)) WEXITSTATUS(fstatus);
			printf("Stopped!\n");
			exit(EXIT_SUCCESS);
		} else {
			execlp("reset", "reset", NULL);
			exit(EXIT_SUCCESS);
		}
	}
}

int print_text(char *s1, char *s2)
{
	int num_incorrect = 0;
	int i = 0;
	//determine whether each char of what user has typed is correct
	for (i; s2[i]; i++) {
		if (s1[i] == s2[i]) {
			if (s1[i] != ' ') printf("%s%s%c%s", ANSI_BLACK, ANSI_BG_GREEN, s1[i], ANSI_RESET);
			else printf("%s%c%s", ANSI_BG_GREEN, s1[i], ANSI_RESET); //if space set bg color only
		}
		else {
			if (s1[i] != ' ') printf("%s%s%c%s", ANSI_BLACK, ANSI_BG_RED, s1[i], ANSI_RESET);
			else printf("%s%c%s", ANSI_BG_RED, s1[i], ANSI_RESET); //if space set bg color only
			num_incorrect++;
		}
	}
	//print everything else from excerpt out
	for (i; s1[i]; i++) printf("%s%c%s", ANSI_YELLOW, s1[i], ANSI_RESET);

	//flush
	printf("\n");

	return num_incorrect;
}

int count_correct(char *s1, char *s2)
{
	int num_correct = 0;
	int i = 0;
	for (i = 0; s1[i]; i++) {
		if (s1[i] == s2[i]) num_correct++;
	}
	return num_correct;
}

int count_incorrect(char *s1, char *s2)
{
	int num_incorrect = 0;
	int i = 0;
	for (i = 0; s2[i]; i++) {
		if (s1[i] != s2[i]) num_incorrect++;
	}
	return num_incorrect;
}

int all_correct(char *s1, char *s2)
{
	int i;
	for (i = 0; s1[i]; i++) {
		if (s1[i] != s2[i]) return 0;
	}
	return 1;
}

double timer()
{
	double time;
	struct timeval timecheck;

	gettimeofday(&timecheck, NULL);
	time = (long)timecheck.tv_sec * 1000 + (double)timecheck.tv_usec / 1000;
	return time;
}

int calculate_wpm(int num_typed, char *s1, char *s2, double t1, double t2)
{
	if ((int)round(((double)num_typed / CHARS_PER_WORD - count_incorrect(s1, s2)) / ((t2 - t1) / 1000 / 60)) < 0) return 0;
	return (int)round(((double)num_typed / CHARS_PER_WORD - count_incorrect(s1, s2)) / ((t2 - t1) / 1000 / 60));
}

double calculate_accuracy(int accu_counter, char *s1, char *s2)
{
	if (accu_counter == 0) return 100;
	return (double)100 * count_correct(s1, s2) / accu_counter;
}

int last_word_correct(int pos, char *s1, char *s2)
{
	if (s1[pos] == ' ' && s2[pos] == ' ') {
		pos--;
		while (pos >= 0) {
			if (s1[pos] != s2[pos]) return 0;
			pos--;
		}
		return 1;
	}
	return 0;
}

void write_results(double time, int WPM, double accuracy)
{
	int results = open("results", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (results == -1) printf("Error: %s\n", strerror(errno));
	char *string = calloc(100, 1);
	string[strlen(string)] = '\0';
	sprintf(string, "%s%0.2lf\n%s%d\n%s%0.1lf%%\n", "Time: ", time, "WPM: ", WPM, "Accuracy: ", accuracy);
	if (write(results, string, strlen(string)) == -1) printf("Error: %s\n", strerror(errno));
	free(string);
	if (close(results) == -1) printf("Error: %s\n", strerror(errno));
}

char *choose(char letter)
{
	switch(letter) {
		case 'a':
			return "It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way – in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.";
		case 'b':
			return "The first little pig was very lazy. He didn't want to work at all and he built his house out of straw. The second little pig worked a little bit harder but he was somewhat lazy too and he built his house out of sticks. Then, they sang and danced and played together the rest of the day.";
		case 'c':
			return "There were other things in the stocking, nuts and oranges and a toy engine, and chocolate almonds and a clockwork mouse, but the Rabbit was quite the best of all. For at least two hours the Boy loved him, and then Aunts and Uncles came to dinner, and there was a great rustling of tissue paper and unwrapping of parcels, and in the excitement of looking at all the new presents the Velveteen Rabbit was forgotten.";
		case 'd':
			return "Saying this, he hung the badger up to the rafters of his storehouse and went out to his work in the fields. The badger was in great distress, for he did not at all like the idea of being made into soup that night, and he thought and thought for a long time, trying to hit upon some plan by which he might escape. It was hard to think clearly in his uncomfortable position, for he had been hung upside down. Very near him, at the entrance to the storehouse, looking out towards the green fields and the trees and the pleasant sunshine, stood the farmer's old wife pounding barley. She looked tired and old. Her face was seamed with many wrinkles, and was as brown as leather, and every now and then she stopped to wipe the perspiration which rolled down her face.";
		case 'e':
			return "The grandmother lived out in the wood, half a league from the village, and just as Little Red Riding Hood entered the wood, a wolf met her. Little Red Riding Hood did not know what a wicked creature he was, and was not at all afraid of him.";
		case 'f':
			return "Then they danced and skipped and leapt over chairs and benches. At last they danced out of doors. From that time forth they came no more, but as long as the shoemaker lived all went well with him, and all his undertakings prospered.";
		case 'g':
			return "So, all in a hurry to see how the stone would keep the gate open, she trotted off down the hill till she came to her own cottage. She unlatched the gate and then turned to unfasten her shawl from the stone which lay on the path behind her. Aye! It was a stone sure enough. There was plenty light to see it lying there, douce and peaceable as a stone should.";
		case 'h':
			return "Accordingly, the good lady bundled up her darlings in woollen jackets and wadded sacks, and put comforters round their necks, and a pair of striped gaiters on each little pair of legs, and worsted mittens on their hands, and gave them a kiss apiece, by way of a spell to keep away Jack Frost. Forth sallied the two children, with a hop-skip-and-jump, that carried them at once into the very heart of a huge snow-drift, whence Violet emerged like a snow-bunting, while little Peony floundered out with his round face in full bloom. Then what a merry time had they! To look at them, frolicking in the wintry garden, you would have thought that the dark and pitiless storm had been sent for no other purpose but to provide a new plaything for Violet and Peony; and that they themselves had been created, as the snow-birds were, to take delight only in the tempest, and in the white mantle which it spread over the earth.";
		case 'i':
			return "In vain did the poor old father weep and implore her pity; she was firm, and he dared not gainsay her. So he placed his daughter in a sledge, not even daring to give her a horse-cloth to keep herself warm with, and drove her out on to the bare, open fields, where he kissed her and left her, driving home as fast as he could, that he might not witness her miserable death.";
		case 'j':
			return "Once upon a time there was a wicked sprite, indeed he was the most mischievous of all sprites. One day he was in a very good humor, for he had made a mirror with the power of causing all that was good and beautiful when it was reflected therein, to look poor and mean; but that which was good-for-nothing and looked ugly was shown magnified and increased in ugliness. In this mirror the most beautiful landscapes looked like boiled spinach, and the best persons were turned into frights, or appeared to stand on their heads; their faces were so distorted that they were not to be recognised; and if anyone had a mole, you might be sure that it would be magnified and spread over both nose and mouth.";
		case 'k':
			return "No sooner were the ceremonies of the wedding over but the mother-in-law began to show herself in her true colors. She could not bear the good qualities of this pretty girl, and the less because they made her own daughters appear the more odious. She employed her in the meanest work of the house: she scoured the dishes, tables, etc., and scrubbed madam's chamber, and those of misses, her daughters; she lay up in a sorry garret, upon a wretched straw bed, while her sisters lay in fine rooms, with floors all inlaid, upon beds of the very newest fashion, and where they had looking-glasses so large that they might see themselves at their full length from head to foot.";
		case 'l':
			return "Deserted by her father, the poor girl sat down under a fir-tree at the edge of the forest and began to weep silently. Suddenly she heard a faint sound: it was King Frost springing from tree to tree, and cracking his fingers as he went. At length he reached the fir-tree beneath which she was sitting, and with a crisp crackling sound he alighted beside her, and looked at her lovely face.";
		case 'm':
			return "Rikki-tikki knew better than to waste time in staring. He jumped up in the air as high as he could go, and just under him whizzed by the head of Nagaina, Nag's wicked wife. She had crept up behind him as he was talking, to make an end of him. He heard her savage hiss as the stroke missed. He came down almost across her back, and if he had been an old mongoose he would have known that then was the time to break her back with one bite; but he was afraid of the terrible lashing return stroke of the cobra. He bit, indeed, but did not bite long enough, and he jumped clear of the whisking tail, leaving Nagaina torn and angry.";
		case 'n':
			return "Though Aesop's own story is a result of myth and legend, it is widely believed that he was a slave from Phrygia, around 600 BC. Aesop lived at the court of King Croesus, after having served many masters as a slave. He shared his wisdom and clever wit by telling humorous tales, while serving on several missions at the pleasure of the King.";
		case 'o':
			return "One bright day in late autumn a family of Ants were bustling about in the warm sunshine, drying out the grain they had stored up during the summer, when a starving Grasshopper, his fiddle under his arm, came up and humbly begged for a bite to eat.";
		case 'p':
			return "In the year 280, in a town in Cappadocia, was born that great soldier and champion of the oppressed whom we call St. George. His parents were Christians, and by them, and especially by his mother, he was most carefully instructed and trained.";
		case 'q':
			return "Far out in the ocean the water is as blue as the petals of the loveliest cornflower, and as clear as the purest glass. But it is very deep too. It goes down deeper than any anchor rope will go, and many, many steeples would have to be stacked one on top of another to reach from the bottom to the surface of the sea. It is down there that the sea folk live.";
		case 'r':
			return "One day the Little Red Hen found a Seed. It was a Wheat Seed, but the Little Red Hen was so accustomed to bugs and worms that she supposed this to be some new and perhaps very delicious kind of meat. She bit it gently and found that it resembled a worm in no way whatsoever as to taste although because it was long and slender, a Little Red Hen might easily be fooled by its appearance.";
		case 's':
			return "There was once upon a time a fisherman who lived with his wife in a pig-stye close by the sea, and every day he went out fishing. And he fished, and he fished. And once he was sitting with his rod, looking at the clear water, and he sat and he sat. Then his line suddenly went down, far down below, and when he drew it up again, he brought out a large flounder.";
		case 't':
			return "The little brook ran along over its pathway of gold, here pausing to form a pool, in which minnows were darting to and fro; and then it hurried onward at a swifter pace, as if in haste to reach the lake; and, forgetting to look whither it went, it tumbled over the root of a tree, which stretched quite across its current. You would have laughed to hear how noisily it babbled about this accident. And even after it had run onward, the brook still kept talking to itself, as if it were in a maze. It was wonder-smitten, I suppose, at finding its dark dell so illuminated, and at hearing the prattle and merriment of so many children. So it stole away as quickly as it could, and hid itself in the lake.";
		case 'u':
			return "But at last, and after his supper, he was put to sleep in the shed on a little truss of hay, under an old blanket, where, as soon as he was alone, he began to whimper for his mother. But the children did not hear him; they had trooped up-stairs to their own beds, all of them as tired as the cub himself, and were presently sound asleep.";
		case 'v':
			return "Once, in the old, old times a fountain gushed out of a hill-side, in the marvellous land of Greece. And, for aught I know, after so many thousand years, it is still gushing out of the very selfsame spot. At any rate, there was the pleasant fountain, welling freshly forth and sparkling adown the hill-side, in the golden sunset, when a handsome young man named Bellerophon drew near its margin. In his hand he held a bridle, studded with brilliant gems, and adorned with a golden bit. Seeing an old man, and another of middle age, and a little boy, near the fountain, and likewise a maiden, who was dipping up some of the water in a pitcher, he paused, and begged that he might refresh himself with a draught.";
		case 'w':
			return "Nevertheless, it was the suddenness with which she had perceived the bull, rather than anything frightful in his appearance, that caused Europa so much alarm. On looking at him more attentively, she began to see that he was a beautiful animal, and even fancied a particularly amiable expression in his face. As for his breath--the breath of cattle, you know, is always sweet--it was as fragrant as if he had been grazing on no other food than rosebuds, or at least, the most delicate of clover blossoms. Never before did a bull have such bright and tender eyes, and such smooth horns of ivory, as this one. And the bull ran little races, and capered sportively around the child; so that she quite forgot how big and strong he was, and, from the gentleness and playfulness of his actions, soon came to consider him as innocent a creature as a pet lamb.";
		case 'x':
			return "Being too proud to allow her son to go to the great house in his ragged clothes, she made him a new suit out of a pretty blue dress she had herself worn in happier times, and when it was finished and the boy dressed in it, he looked as pretty as a prince in a fairy tale. For the bright blue jacket set off his curls to good advantage, and the color just matched the blue of his eyes. His trousers were blue, also, and she took the silver buckles from her own shoes and put them on his, that he might appear the finer. And then she brushed his curls and placed his big straw hat upon them and sent him away with a kiss to see the Squire.";
		case 'y':
			return "Embosomed amongst a family of lofty mountains, there was a valley so spacious that it contained many thousand inhabitants. Some of these good people dwelt in log-huts, with the black forest all around them, on the steep and difficult hill-sides. Others had their homes in comfortable farm-houses, and cultivated the rich soil on the gentle slopes or level surfaces of the valley. Others, again, were congregated into populous villages, where some wild, highland rivulet, tumbling down from its birthplace in the upper mountain region, had been caught and tamed by human cunning, and compelled to turn the machinery of cotton-factories. The inhabitants of this valley, in short, were numerous, and of many modes of life. But all of them, grown people and children, had a kind of familiarity with the Great Stone Face, although some possessed the gift of distinguishing this grand natural phenomenon more perfectly than many of their neighbors.";
		case 'z':
			return "The little fellow had a great opinion of his own strength. So, grasping the rough protuberances of the rock, he tugged and toiled amain, and got himself quite out of breath, without being able to stir the heavy stone. It seemed to be rooted into the ground. No wonder he could not move it; for it would have taken all the force of a very strong man to lift it out of its earthy bed. His mother stood looking on, with a sad kind of a smile on her lips and in her eyes, to see the zealous and yet puny efforts of her little boy. She could not help being sorrowful at finding him already so impatient to begin his adventures in the world.";
	}
}

void play(char *name, int pipefd[], char letter)
{

	signal(SIGINT, sighandler);

	/* printf("%s\n", readline("test> ")); */

	/* int exit_status = system("gnome-terminal"); */

	double start, t, end, total;
	struct timeval timecheck;

	struct termios old, new;
	tcgetattr(STDIN_FILENO, &old);
	tcgetattr(STDIN_FILENO, &new); //get current terminal attributes
	/* new.c_lflag &= ~(ICANON | ECHO); */
	new.c_lflag &= ~ICANON; //disable canonical mode
	new.c_cc[VMIN] = 1; //wait until at least one keystroke available
	new.c_cc[VTIME] = 0; //no timeout
	tcsetattr(STDIN_FILENO, TCSANOW, &new); //set immediately

	char base_str[1024];
	strcpy(base_str, choose(letter));
	char *input = calloc(strlen(base_str) + 1, 1);
	input[strlen(base_str)] = '\0';

	int pos = 0;
	char block_off = 1; //when user makes too many mistakes, input is blocked
	int num_typed = 0;
	int accu_counter = 0;

	gettimeofday(&timecheck, NULL);
	start = (long)timecheck.tv_sec * 1000 + (double)timecheck.tv_usec / 1000;

	//start timer
	while ((timer() - start) <= 3000) {
		printf("%d...\n", 3 - (int)((timer() - start) / 1000));
		clear_screen();
	}

	printf("%s\n", base_str);

	while (!all_correct(base_str, input)) {
		char c = getchar();
		clear_screen();
		if (pos < strlen(base_str) && block_off && c != BACKSPACE && c != 127) {
			if (base_str[pos] != c) {
				if (!fork()) {
					execlp("echo", "echo", "-en", "\a", NULL); //sound!!!
					exit(EXIT_SUCCESS);
				}
			}
			input[pos] = c;
			pos++;
			num_typed++;
			accu_counter++;
		} else if (c == BACKSPACE || c == 127) {
			if (!last_word_correct(pos - 1, base_str, input)) {
				if (pos > 0) {
					pos--;
					num_typed--;
					if (base_str[pos] == input[pos]) accu_counter--;
				}
				else if (pos == 0) pos = 0;
				input[pos] = '\0';
			}
		} else {
			if (!fork()) {
				execlp("echo", "echo", "-en", "\a", NULL); //sound!!!
				exit(EXIT_SUCCESS);
			}
		}
		//block user input if necessary
		int num_incorrect = print_text(base_str, input);
		if (num_incorrect > 4) block_off = 0;
		else block_off = 1;

		gettimeofday(&timecheck, NULL);
		t = (long)timecheck.tv_sec * 1000 + (double)timecheck.tv_usec / 1000;
		printf("WPM: %d\n", calculate_wpm(num_typed, base_str, input, start, t));
		printf("Accuracy: %0.1lf%%\n", calculate_accuracy(accu_counter, base_str, input));

		char stats[256];
		int wpm = calculate_wpm(num_typed, base_str, input, start, t);
		double accuracy = calculate_accuracy(accu_counter, base_str, input);
		int words_correct = count_correct(base_str, input);
		sprintf(stats, "%s %d %0.1lf %d", name, wpm, accuracy, words_correct);
		write(pipefd[WRITE], stats, sizeof(stats));
	}

	gettimeofday(&timecheck, NULL);
	end = (long)timecheck.tv_sec * 1000 + (double)timecheck.tv_usec / 1000;
	total = end - start; //total elapsed time in milliseconds

	int f = fork();
	if (f) {
		int fstatus;
		waitpid(f, &fstatus, 0);
		if (WIFEXITED(fstatus)) WEXITSTATUS(fstatus);
		printf("\n%s\n", input);
		printf("Time: %0.2lf seconds\n", total / 1000);
		printf("Average WPM: %d\n", calculate_wpm(num_typed, base_str, input, start, end));
		printf("Accuracy: %0.1lf%%\n", calculate_accuracy(accu_counter, base_str, input));
		write_results(total / 1000, calculate_wpm(num_typed, base_str, input, start, end), calculate_accuracy(accu_counter, base_str, input));
		free(input);
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
	} else {
		execlp("reset", "reset", NULL);
		exit(EXIT_SUCCESS);
	}
}
