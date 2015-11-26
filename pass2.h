int prog_size;

void pass_2()
{
    int start_add, i,locctr,address,flag,length,val,optab_val,symtab_val;
    char opcode[20],label[20],check[20],count[20];

    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("intermediate.txt","r");
    fp4=fopen("output.txt","w");

    fscanf(fp1,"%s %s %X",&label,&opcode,&start_add);
    fprintf(fp4,"%s\t%s\t%X\n",label,opcode,start_add);




    while(!feof(fp1))
    {
        fscanf(fp1,"%X %s %s %s",&locctr,&label,&opcode,&count);


        if(strcmp(label,"-")==0)
        {
            flag=0;
            fp2=fopen("optab.txt","r");
            while(!feof(fp2))
            {
                fscanf(fp2,"%s %d %d",&check,&length,&val);
                if(strcmp(opcode,check)==0)
                {
                    optab_val=val;
                    flag++;
                    break;

                }
            }
            fclose(fp2);

            fp3=fopen("symtab.txt","r");
            while(!feof(fp3))
            {
                fscanf(fp3,"%s %x",&check,&val);
                if(strcmp(count,check)==0)
                {
                    symtab_val=val;
                    flag++;
                    break;
                }
            }
            fclose(fp3);

            if(flag==2)
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t%02d%X\n",locctr,label,opcode,count,optab_val,symtab_val);
            }


        /*  else if(strcmp(opcode,"END")==0)
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t-\n",locctr,label,opcode,count);  //For END
            }
        */


        }


         else
        {

            if(strcmp(opcode,"WORD")==0)
            {
                fprintf(fp4,"%x\t%s\t%s\t%s\t%06s\n",locctr,label,opcode,count,count);
            }


            else if(strcmp(opcode,"BYTE")==0)
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t",locctr,label,opcode,count);
                for(i=2;i<strlen(count)-1;i++)
                {
                    fprintf(fp4,"%c",count[i]);
                }
                fprintf(fp4,"\n");
            }

            else if((strcmp(opcode,"RESW")==0) || (strcmp(opcode,"RESB")==0))
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t-\n",locctr,label,opcode,count);
            }


            else
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t-\n",locctr,label,opcode,count);
            }

        }



    }

    prog_size=locctr-start_add;

    fprintf(fp4,"%X\t%s\t%s\t%s\t-\n",locctr,label,opcode,count);
    fclose(fp4);

    printf("Output.txt file generated\n");
}





void object_pro()
{
    int start_add, text_add, size=0,locctr;
    int check,length;
    char pro_name[20], opcode[20],count[20],label[20],instruct[20],temp[20];

    FILE *fp1,*fp2,*fp3;

    fp1=fopen("output.txt","r");
    fp2=fopen("objectprogram.txt","w");


    fscanf(fp1,"%s %s %X",&pro_name,&opcode,&start_add);
    fprintf(fp2,"H ^ %s ^ %06X ^ %X",pro_name,start_add,prog_size);

    while(!feof(fp1))
    {

        size=0;
        fp3=fopen("temp.txt","w");
        while(size<=30)
        {

            /*if((strcmp(opcode,RESB)==0) || (strcmp(opcode,RESB)==0))
            {
                break;
            }
            */

            fscanf(fp1,"%X %s %s %s %s",&locctr,&label,&opcode,&count,&instruct);

            if(strcmp(instruct,"-")==0)
            {
                break;
            }
            else
            {
                if(size==0)
                {
                    text_add=locctr;
                }
                size=size+(strlen(instruct)/2);
                fprintf(fp3,"^ %s ",instruct);
            }


        }


        fprintf(fp3,"endline");
        fclose(fp3);


        if(size>0)
        {

            fprintf(fp2,"\nT ^ %06X ^ %02X",text_add,size);

            fp3=fopen("temp.txt","r");
            while(!feof(fp3))
            {

                fscanf(fp3,"%s",&temp);
                if(strcmp(temp,"endline")==0)
                {
                    break;
                }
                fprintf(fp2," %s ",temp);
            }
            fclose(fp3);

        }


    }


    fprintf(fp2,"\nE ^ %06X",start_add);

    fclose(fp2);

printf("Objectprogram.txt file generated\n");
printf("Pass 2 completed\n");
}
