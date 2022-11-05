#define COMMA ,

#define DEF_JMP(name, num, sign)                                \
            DEF_CMD(name, num,                                  \
                        POP(&second_operand);                   \
                        POP(&first_operand);                    \
                        if (first_operand sign second_operand)  \
                        {                                       \
                            if (ARG(1) < 0) SegFault();         \
                            IP = ARG(1);                        \
                        }                                       \
                        else                                    \
                        {                                       \
                            IP += 2;                            \
                        }                                       \
                    )                                           

DEF_CMD(PUSH, 1,
            int *arg = ProcArgsPushAndPop(CMD, CPU, &(ARG(1)), false);
            IP += 2;
            PUSH(*arg);
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
            PUSH(first_operand * second_operand / 100);
            IP++;
        )

DEF_CMD(DIV, 5,
            POP(&first_operand);
            POP(&second_operand);
            assert(first_operand != 0);
            PUSH(second_operand * 100/ first_operand);
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
            double ans = (double)first_operand/100;
            printf("Value: %.2lf\n", ans);
            fprintf(CPU->result, "Result = %.2lf\n", ans);
            IP++;
        )

DEF_CMD(JMP, 8,
            if (ARG(1) < 0) SegFault();
            IP = ARG(1);
        )

DEF_JMP(JB,   9,  <)

DEF_JMP(JBE, 10, <=)

DEF_JMP(JA,  11,  >)

DEF_JMP(JAE, 12, >=)

DEF_JMP(JE,  13, ==)

DEF_JMP(JNE, 14, !=)

DEF_CMD(POP, 15, 
            int *place = ProcArgsPushAndPop(CMD, CPU, &(ARG(1)), true);
            int arg = 0;
            POP(&arg);
            *place = arg;
            IP += 2;
        )

DEF_CMD(DUMP, 16,
            Dump(CPU);
            IP++;
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
            Paint(ARG(1), window_width, window_height, &RAM(REG(0)));
            IP += 2;
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
                
                int mes_len = 22;
                if (window_width - x > mes_len && rand()%1000 == 1)
                {
                    for (int i = 0; i < mes_len; ++i)
                    {
                        strncpy(line + x, "My mentor, I call you!", mes_len);
                    }
                    x += mes_len -1;
                }
                else
                {
                    char ch = 0;
                    if (RAM(point) == 0) ch = ' ';
                    else
                    {   
                        ch = (rand()%10 > 5) ? rand()%10 + '0' : ' ';
                    } 
                    line[x] = ch;
                }
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
            POP(&first_operand);
            PUSH(sqrt(first_operand) * 10);
            IP++;
            )

DEF_CMD(IN, 25,
            scanf("%d", &first_operand);
            PUSH(first_operand);
            IP++;
        )

DEF_CMD(NOP, 0x90,
            do 
            {
                IP++;
            } while (CMD == CMD_NOP);
        )

DEF_CMD(HLT, 27,
            assert(!fclose(CPU->result));
            return;
        )

#undef COMMA