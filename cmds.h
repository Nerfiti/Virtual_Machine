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
            int place = 0;
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

DEF_CMD(HLT, 19,
            assert(!fclose(CPU->result));
            return;
        )