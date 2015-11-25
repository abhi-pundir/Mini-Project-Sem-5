int pass_1()
{
    int start_add,locctr,address,flag,length,val,temps;
    char opcode[20],label[20],check[20],count[20];

    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("input.txt","r");
    //fp2=fopen("optab.txt","r");
    //fp3=fopen("symtab.txt","r");
    fp4=fopen("intermediate.txt","w");


    fscanf(fp1,"%s %s %X",&label,&opcode,&address);

    if(strcmp(opcode,"START")==0)
    {
        start_add=address;
        locctr=start_add;
        fprintf(fp4,"%s\t%s\t%X\n",label,opcode,address);
        fscanf(fp1,"%s %s %s",&label,&opcode,&count);
    }
    else
    {
        locctr=0;
    }



    while(strcmp(opcode,"END")!=0)
    {
        fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,label,opcode,count);


        if(strcmp(label,"-")!=0)
        {
                flag=0;
                fp3=fopen("symtab.txt","r");

                while(!feof(fp3))
                {
                    fscanf(fp3,"%s %X",&check,&address);
                    if(strcmp(check,label)==0)
                    {
                        flag=1;

                    }

                }
                fclose(fp3);

                if(flag==0)
                {
                    fp3=fopen("symtab.txt","a");
                    fprintf(fp3,"%s %X\n",label,locctr);
                }

        }


        fp2=fopen("optab.txt","r");
        flag=0;
        while(!feof(fp2))
        {

            fscanf(fp2,"%s %d %d",&check,&length,&val);
            if(strcmp(check,opcode)==0)
            {
                flag=1;
                break;
            }
        }
        fclose(fp2);

           if(flag==1)
            {
                locctr+=length;
            }
            else if(strcmp(opcode,"WORD")==0)
            {
                locctr+=3;
            }
            else if(strcmp(opcode,"RESW")==0)
            {
                /*temps=0;
                for(i=0;i<strlen(count);i++)
                {
                    temps=(temps*10)+count[i];
                }*/
                sscanf(count,"%d",&temps);
                locctr+=3*temps;
            }
            else if(strcmp(opcode,"RESB")==0)
            {
                /*temps=0;
                //for(i=0;i<strlen(count);i++)
                //{
                //    temps=(temps*10)+count[0];
                }*/
                sscanf(count,"%d",&temps);
                locctr+=temps;
            }
            else if(strcmp(opcode,"BYTE")==0)
            {
                locctr+=(strlen(count)-3)/2;
            }


        fscanf(fp1,"%s %s %s",&label,&opcode,&count);

    }

    fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,label,opcode,count);
    fclose(fp4);
    fclose(fp1);
}
