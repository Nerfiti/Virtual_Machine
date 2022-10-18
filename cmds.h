DEF_CMD(PUSH, 1,
            int arg = 0;
            if ((CMD & With_RAM) && (CMD & With_REG) && (CMD & With_PLUS))
            {
                arg = RAM(ARG(1) + REG(ARG(2)));
                IP++;
            }
            else if ((CMD & With_RAM) && (CMD & With_REG)) arg = RAM(REG(1));
            else if (CMD & With_RAM)                      arg = RAM(ARG(1));
            else if (CMD & With_REG)                      arg = REG(ARG(1));
            else                                          arg = ARG(1);
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
            IP = ARG(1);
        )

DEF_CMD(JB, 9,
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
            int place = 0;
            if ((CMD & With_RAM) && (CMD & With_REG) && (CMD & With_PLUS))
            {
                RAM(ARG(1) + REG(ARG(2))) = arg;
                IP++;
            }
            else if ((CMD & With_RAM) && (CMD & With_REG)) RAM(REG(ARG(1))) = arg;
            else if (CMD & With_RAM)                       RAM(ARG(1))      = arg;
            else if (CMD & With_REG)                       REG(ARG(1))      = arg;
            IP += 2;
        )

DEF_CMD(HLT, 16,
            assert(!fclose(CPU->result));
            return;
        )