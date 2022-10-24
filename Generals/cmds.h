#define COMMA ,

DEF_CMD(PUSH, 1,
            int arg = 0;
            if ((CMD & With_RAM) && (CMD & With_REG) && (CMD & With_PLUS))
            {
                arg = RAM(ARG(1) + REG(ARG(2)));
                if (arg < 0 || arg > size_of_ram) SegFault();
                IP++;
            }
            else if ((CMD & With_RAM) && (CMD & With_REG)) arg = RAM(REG(1));
            else if (CMD & With_RAM)                       arg = RAM(ARG(1));
            else if (CMD & With_REG)                       arg = REG(ARG(1));
            else                                           arg = ARG(1);
            IP += 2;
            PUSH(arg);
        )

DEF_CMD(ADD, 2,
            POP(&first_operand);
            POP(&second_operand);
            PUSH(first_operand + second_operand);
            IP++;
        )

DEF_CMD(SUB, 3,
            POP(&first_operand);
            POP(&second_operand);
            PUSH(second_operand - first_operand);
            IP++;
        )

DEF_CMD(MUL, 4,
            POP(&first_operand);
            POP(&second_operand);
            PUSH(first_operand * second_operand);
            IP++;
        )

DEF_CMD(DIV, 5,
            POP(&first_operand);
            POP(&second_operand);
            assert(first_operand != 0);
            PUSH(second_operand / first_operand);
            IP++;
        )

DEF_CMD(DUP, 6,
            POP(&first_operand);
            PUSH(first_operand);
            PUSH(first_operand);
            IP++;
        )

DEF_CMD(OUT, 7,
            POP(&first_operand);
            printf("Value: %d\n", first_operand);
            fprintf(CPU->result, "Result = %d\n", first_operand);
            IP++;
        )

DEF_CMD(JMP, 8,
            if (ARG(1) < 0) SegFault();
            IP = ARG(1);
        )

DEF_CMD(JB, 9,
            if (ARG(1) < 0) SegFault();
            POP(&second_operand);
            POP(&first_operand);
            if (first_operand < second_operand)
            {
                IP = ARG(1);
            }
            else
            {
                IP += 2;
            }
        )

DEF_CMD(JBE, 10,
            if (ARG(1) < 0) SegFault();
            POP(&second_operand);
            POP(&first_operand);
            if (first_operand <= second_operand)
            {
                IP = ARG(1);
            }
            else
            {
                IP += 2;
            }
        )

DEF_CMD(JA, 11,
            if (ARG(1) < 0) SegFault();
            POP(&second_operand);
            POP(&first_operand);
            if (first_operand > second_operand)
            {
                IP = ARG(1);
            }
            else
            {
                IP += 2;
            }
        )

DEF_CMD(JAE, 12,
            if (ARG(1) < 0) SegFault();
            POP(&second_operand);
            POP(&first_operand);
            if (first_operand >= second_operand)
            {
                IP = ARG(1);
            }
            else
            {
                IP += 2;
            }
        )

DEF_CMD(JE, 13,
            if (ARG(1) < 0) SegFault();
            POP(&second_operand);
            POP(&first_operand);
            if (first_operand == second_operand)
            {
                IP = ARG(1);
            }
            else
            {
                IP += 2;
            }
        )

DEF_CMD(JNE, 14,
            if (ARG(1) < 0) SegFault();
            POP(&second_operand);
            POP(&first_operand);
            if (first_operand != second_operand)
            {
                IP = ARG(1);
            }
            else
            {
                IP += 2;
            }
        )

DEF_CMD(POP, 15, 
            int arg = 1;
            POP(&arg);
            if ((CMD & With_RAM) && (CMD & With_REG) && (CMD & With_PLUS))
            {
                RAM(ARG(1) + REG(ARG(2))) = arg;
                IP++;
            }
            else if ((CMD & With_RAM) && (CMD & With_REG)) RAM(REG(ARG(1))) = arg;
            else if (CMD & With_RAM)                       RAM(ARG(1))      = arg;
            else if (CMD & With_REG)                       REG(ARG(1))      = arg;
            else SegFault();
            IP += 2;
        )

DEF_CMD(DUMP, 16,
            StackDump(STACK);
            IP++;
            int start = (0 > IP - 4) ? 0 : IP - 4;
            int finish = 0;
            for (int i = 0; i <= 4; ++i)
            {
                finish = IP + i;
                if (CODE[IP + i] == CMD_HLT) break;
            }
            printf("IP   --| ");
            for (int i = start; i < finish; ++i)
            {
                printf(" %3d " COMMA i);
            }
            printf(" |--\n" "CODE --| ");
            for (int i = start; i < finish; ++i)
            {
                printf(" %3d " COMMA CODE[i] & cmd_id_mask);
            }
            printf(" |--\n      ");
            for (int i = start; i < IP; ++i)
            {
                printf("     ");
            }
            printf("^\n      ");
            for (int i = start; i < IP; ++i)
            {
                printf("     ");
            }
            printf("| Instruction Pointer (IP)\n");
            system("pause");
        )

DEF_CMD(CALL, 17,
            if (ARG(1) < 0 || ARG(1) > size_of_ram) SegFault();
            RETPUSH(IP + 2);
            IP = ARG(1);
        )

DEF_CMD(RET, 18,
            RETPOP(&IP);
            if (IP < 0 || IP > size_of_ram) SegFault();
)

DEF_CMD(PNT, 19,
            char screen[window_width*window_height + 1] = "";
            char line  [window_width + 1] = "";
            for (int y = 0; y < window_height; ++y)
            {
                for (int x = 0; x < window_width; ++x)
                {
                    int point = REG(ARG(1)) + x + window_width * y;
                    
                    char ch = 0;
                    if (RAM(point) == 0) ch = ' ';
                    else ch = '*';

                    screen[point - REG(ARG(1))] = ch;
                }
                screen[(y+1)*window_width - 1] = '\n';
            }
            printf("%s", screen);
            REG(0) = 300 + REG(ARG(1))%10 + 1;
            IP++;
        )

DEF_CMD(RND, 20,
            PUSH(rand());
            IP++;
        )

DEF_CMD(SLP, 21,
            Sleep(ARG(1));
            IP += 2;
        )

DEF_CMD(MTX, 22,
            
            char line [window_width + 1] = "";
            for (int x = 0; x < window_width; ++x)
            {
                int point = REG(0) + x;
                
                char ch = 0;
                if (RAM(point) == 0) ch = ' ';
                else
                {
                    ch = (rand()%10 > 5) ? rand()%10 + '0' : ' ';
                } 
                line [x] = ch;
            }
            printf("%s\n", line);
            IP++;
        )

DEF_CMD(COLOR, 23,
            int cmd_len = 20;
            char cmd[cmd_len] = "";
            sprintf(cmd, "color %.2p" COMMA ARG(1));
            system(cmd);
            IP += 2;
        )

DEF_CMD(SQR, 24,
            const int max_ans_len = 100;
            int a = 0;
            int b = 0;
            int c = 0;
            double x1 = 0;
            double x2 = 0;
            NumberOfRoots nRoots = NO_ROOTS;
            char ans[max_ans_len] = "";

            POP(&c);
            POP(&b);
            POP(&a);

            nRoots = solveSquare(a, b, c, &x1, &x2);

            sPrintAnswer(ans, nRoots, x1, x2);
            printf("%s", ans);
            fprintf(CPU->result, "%s", ans);
            IP++;
            )

DEF_CMD(HLT, 25,
            assert(!fclose(CPU->result));
            return;
        )

#undef COMMA