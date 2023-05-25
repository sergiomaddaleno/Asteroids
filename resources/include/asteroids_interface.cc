
//The 2 starting squares
TBox box1 = {{95,350},{365,460}, {35,82,200}};
TBox box2 = {{805,350},{1075,460}, {35,82,200}};

//The 2 identify squares
TBox boxIdent = {{400,300},{840,370}, {35,82,200}};
TBox boxPass = {{400,400},{840,470}, {35,82,200}};

TBox boxLeftBot = {{100,620},{250,700}, {255,10,10}};
TBox boxRightBot = {{940,620},{1090,700}, {255,10,10}};
TBox boxMiddleBot = {{400,620},{600,700}, {255,10,10}};
TBox boxMiddleBot2 = {{670,620},{870,700}, {255,10,10}};
TBox boxMiddleBot3 = {{980,590},{1130,730}, {255,10,10}};

//Register squares
TBox bReg1 = {{350,165},{800,205}, {35,82,200}};
TBox bReg2 = {{350,215},{800,255}, {35,82,200}};
TBox bReg3 = {{350,265},{800,305}, {35,82,200}};
TBox bReg4 = {{350,315},{800,355}, {35,82,200}};
TBox bReg5 = {{350,365},{800,405}, {35,82,200}};
TBox bReg6 = {{350,415},{800,455}, {35,82,200}};
TBox bReg7 = {{350,465},{645,505}, {35,82,200}};
TBox bReg8 = {{674,465},{990,505}, {35,82,200}};

//-----------------------------------------------------
TBox bEdit = {{1067,178},{1110,208}, {35,82,200}};
TBox bDelete = {{1120,178},{1190,208}, {35,82,200}};

TBox bEdit2 = {{1067,228},{1110,258}, {35,82,200}};
TBox bDelete2 = {{1120,228},{1190,258}, {35,82,200}};

TBox bEdit3 = {{1067,278},{1110,308}, {35,82,200}};
TBox bDelete3 = {{1120,278},{1190,308}, {35,82,200}};

TBox bEdit4 = {{1067,328},{1110,358}, {35,82,200}};
TBox bDelete4 = {{1120,328},{1190,358}, {35,82,200}};

TBox bEdit5 = {{1067,378},{1110,408}, {35,82,200}};
TBox bDelete5 = {{1120,378},{1190,408}, {35,82,200}};

TBox bEdit6 = {{1067,428},{1110,458}, {35,82,200}};
TBox bDelete6 = {{1120,428},{1190,458}, {35,82,200}};

TBox bEdit7 = {{1067,478},{1110,508}, {35,82,200}};
TBox bDelete7 = {{1120,478},{1190,508}, {35,82,200}};

TBox bEdit8 = {{1067,528},{1110,558}, {35,82,200}};
TBox bDelete8 = {{1120,528},{1190,558}, {35,82,200}};
//-----------------------------------------------------

TBox bControls = {{900,740},{1060,790}, {35,82,200}};
TBox bClear = {{1050,465},{1150,505}, {35,82,200}};
TBox bAdmin =  {{1040,20},{1180,70}, {255,10,10}};
TBox bPause = {{390,380},{830,470}, {35,82,200}};


bool ControlMouse(TBox r){
    int posx = esat::MousePositionX();
	int posy = esat::MousePositionY();
	if (posx > r.p1.x && posx < r.p2.x && posy > r.p1.y && posy < r.p2.y)
		return true;
	
		else return false;
}

void DrawBox(TBox r) {
    float x1 = r.p1.x;
    float y1 = r.p1.y;
    float x2 = r.p2.x;
    float y2 = r.p2.y;

    float *p=(float*)malloc(8*sizeof(float));
    *(p+0) = x1;
    *(p+1) = y1;
    *(p+2) = x2;
    *(p+3) = y1;
    *(p+4) = x2;
    *(p+5) = y2;
    *(p+6) = x1;
    *(p+7) = y2;

    esat::DrawSetFillColor(r.color.r, r.color.g, r.color.b);
    esat::DrawSolidPath(p, 4);
    free(p);
}

void DrawBlackBox(TBox r){
    float *p=(float*)malloc(9*sizeof(float));
    *(p+0) = r.p1.x;
    *(p+1) = r.p1.y;
    *(p+2) = r.p2.x;
    *(p+3) = r.p1.y;
    *(p+4) = r.p2.x;
    *(p+5) = r.p2.y;
    *(p+6) = r.p1.x;
    *(p+7) = r.p2.y;
    *(p+8) = r.p1.x;
    *(p+9) = r.p1.y;

    esat::DrawSetStrokeColor(255,255,255);
    if(colorMode){
      esat::DrawSetStrokeColor(0,255,255); 
    }
    esat::DrawPath(p, 5);
    free(p);
}

void SetScreen(){
    adminBack=false;

    if(gamestart==false){
        
        esat::DrawSprite(space, 352, 300);
        if(MBmode){esat::DrawSprite(MB, 953, 673);}
        

        esat::DrawSetTextFont("./resources/font/font.ttf");
		esat::DrawSetFillColor(255, 255, 255);
        esat::DrawSetTextSize(120.0f);

        if(colorMode){esat::DrawSetFillColor(138,43,226);}

		esat::DrawText(140, 160, "ASTEROIDS");
        esat::DrawSetTextFont("./resources/font/fontV3.ttf");

        esat::DrawSetFillColor(35, 82, 176);
        esat::DrawSetTextSize(15.0f);
        esat::DrawText(10, 30, "Press    to show scores");
        esat::DrawSprite(tab, 100, 10);

        esat::DrawSetTextSize(25.0f);
        esat::DrawText(10, 740, "Recreated by");
        esat::DrawText(10, 780, "Sergio Madaleno");

        //Detect when mouse inside box
		if (ControlMouse(box1)){DrawBox(box1);} else{DrawBlackBox(box1);}
        if (ControlMouse(box2)){DrawBox(box2);} else{DrawBlackBox(box2);}
        if (ControlMouse(bControls)){DrawBox(bControls);} else{DrawBlackBox(bControls);}

        //Change option when click mouse inside box
        if(ControlMouse(box1) && esat::MouseButtonDown(0)){
            esat::ResetBufferdKeyInput();
            identify_=true;
            score = 0;
            strcpy(g_User.userNameLogin, "");
            strcpy(g_User.passwordLogin, "");
        }
        if(ControlMouse(box2) && esat::MouseButtonDown(0)){register_=true;}
        if(ControlMouse(bControls) && esat::MouseButtonDown(0)){controlsinfo_=true;}

		esat::DrawSetTextFont("./resources/font/fontV2.ttf");
		esat::DrawSetTextSize(50.0f);
		esat::DrawSetFillColor(255, 255, 255);
		esat::DrawText(165, 420, "LOGIN");
		esat::DrawText(837, 420, "REGISTER");

        esat::DrawSetTextSize(30.0f);
        esat::DrawText(920, 775, "SETTINGS");

        if(ControlMouse(bAdmin) && esat::MouseButtonDown(0)){adminIdentify_=true; register_=false; startScreen_=false;}
        esat::ResetBufferdKeyInput();
        DrawBlackBox(bAdmin);
        if(ControlMouse(bAdmin)){DrawBox(bAdmin);}
        esat::DrawSetFillColor(255, 255, 255);
        esat::DrawText(1075, 54, "ADMIN");

        //To clear the boxes
        if(ControlMouse(box2) && esat::MouseButtonDown(0)){
            esat::ResetBufferdKeyInput();
            strcpy(g_User.userNameRegister, "");
            strcpy(g_User.passwordRegister, "");
            strcpy(g_User.name, "");
            strcpy(g_User.birthDate, "");
            strcpy(g_User.province, "");
            strcpy(g_User.country, "");
            strcpy(g_User.email, "");
            strcpy(g_User.email2, "");
        }

        if(ControlMouse(bAdmin) && esat::MouseButtonDown(0)){
            esat::ResetBufferdKeyInput();
            strcpy(g_User.userNameLogin, "");
            strcpy(g_User.passwordLogin, "");
        }
    }
}

void HandleTextInput(char *text, int posx, int posy) {
    char getKey_ = esat::GetNextPressedKey();

    if (esat::IsSpecialKeyDown(esat::kSpecialKey_Backspace)) {
        int len = strlen(text);
        if (len > 0) {
            *(text + len - 1) = '\0';
        }
    }

    if (strlen(text) < 19) {
        char newChar[2] = { getKey_, '\0' };
        strcat(text, newChar);
    }

    esat::DrawSetFillColor(255, 255, 255);
    esat::DrawText(posx, posy, text);
}

//---------------------------------------------------------------------------------------------------
//Save data
void WriteNewUser(){

    bool dataEntered = false;
    if (strlen(g_User.name) > 0) dataEntered = true;
    if (strlen(g_User.birthDate) > 0) dataEntered = true;
    if (strlen(g_User.province) > 0) dataEntered = true;
    if (strlen(g_User.country) > 0) dataEntered = true;
    if (strlen(g_User.email) > 0) dataEntered = true;
    if (strlen(g_User.email2) > 0) dataEntered = true;

    if(ControlMouse(boxMiddleBot) && esat::MouseButtonDown(0) && register_ && dataEntered){
        fSave=fopen("UserData.dat", "ab");

        fwrite(g_User.userNameRegister, sizeof(char), 20, fSave);
        fwrite(&score, sizeof(int),1, fSave);
        fwrite(g_User.passwordRegister, sizeof(char), 20, fSave);

        fwrite(g_User.name, sizeof(char), 20, fSave);
        fwrite(g_User.birthDate, sizeof(char), 20, fSave);
        fwrite(g_User.province, sizeof(char), 20, fSave);
        fwrite(g_User.country, sizeof(char), 20, fSave);
        fwrite(g_User.email, sizeof(char), 13, fSave);
        fwrite(g_User.email2, sizeof(char), 14, fSave);

        fclose(fSave);
        startScreen_=true;
        register_=false;
    }
}

void FindUserLogin(){

    int num;
    fSave = fopen("UserData.dat", "rb");
    if(fSave == nullptr){
        return;
    }

    validUser = false;

    while(fread(g_User.userNameRegister, sizeof(char), 20, fSave) != 0){

        fread(g_User.userMaxScore,sizeof(int),1,fSave);
        fread(g_User.passwordRegister, sizeof(char), 20, fSave);

        fread(g_User.name, sizeof(char), 20, fSave);
        fread(g_User.birthDate, sizeof(char), 20, fSave);
        fread(g_User.province, sizeof(char), 20, fSave);
        fread(g_User.country, sizeof(char), 20, fSave);
        fread(g_User.email, sizeof(char), 13, fSave);
        fread(g_User.email2, sizeof(char), 14, fSave);

        if(strcmp(g_User.userNameRegister, g_User.userNameLogin) == 0 && strcmp(g_User.passwordRegister, g_User.passwordLogin) == 0){
            validUser = true;    
            maxScore = *g_User.userMaxScore;
        }
    }
    
    fclose(fSave);
}

void ValidateUser(){

    FindUserLogin();

    if(validUser && ControlMouse(boxRightBot) && esat::MouseButtonDown(0)){
        gamestart = true;
        showScores = true;
    }
    
}
//---------------------------------------------------------------------------------------------------

void IdentifyUserScreen(){

    esat::DrawSetTextFont("./resources/font/fontV3.ttf");
    esat::DrawSetTextSize(50.0f);
    esat::DrawText(100, 200, "USER LOGIN");

    esat::DrawSetTextFont("./resources/font/fontV2.ttf");
	esat::DrawSetTextSize(40.0f);
	esat::DrawSetFillColor(255, 255, 255);

    esat::DrawText(150, 350, "Username:");
    esat::DrawText(150, 450, "Password:");

    //Black box is allways drawn
    DrawBlackBox(boxIdent);
    DrawBlackBox(boxPass);
    DrawBlackBox(boxLeftBot);
    DrawBlackBox(boxRightBot);

    if(ControlMouse(boxIdent)){DrawBox(boxIdent); HandleTextInput(g_User.userNameLogin, 415, 350);}
    if(ControlMouse(boxPass)){DrawBox(boxPass); HandleTextInput(g_User.passwordLogin, 415, 445);}

    if(ControlMouse(boxLeftBot)){DrawBox(boxLeftBot);} 
    if(ControlMouse(boxRightBot)){DrawBox(boxRightBot);} 
    esat::DrawSetFillColor(255, 255, 255);
    if(ControlMouse(boxLeftBot) && esat::MouseButtonDown(0)){back_=true;}

    //Draw again to keep the text in screen
    esat::DrawText(415, 350, g_User.userNameLogin);
    esat::DrawText(415, 445, g_User.passwordLogin);

    esat::DrawSetFillColor(255, 255, 255);
    esat::DrawText(130, 670, "Back");
    esat::DrawText(970, 670, "Play");
    
    
}

void adminIdent(){

    esat::DrawSetTextFont("./resources/font/fontV3.ttf");
    esat::DrawSetTextSize(50.0f);
    esat::DrawText(100, 200, "ADMIN LOGIN");

    esat::DrawSetTextFont("./resources/font/fontV2.ttf");
	esat::DrawSetTextSize(40.0f);
	esat::DrawSetFillColor(255, 255, 255);

    esat::DrawText(150, 350, "Username:");
    esat::DrawText(150, 450, "Password:");

    //Black box is allways drawn
    DrawBlackBox(boxIdent);
    DrawBlackBox(boxPass);
    DrawBlackBox(boxLeftBot);
    DrawBlackBox(boxMiddleBot);

    if(ControlMouse(boxIdent)){DrawBox(boxIdent); HandleTextInput(g_User.userNameLogin, 415, 350);}
    if(ControlMouse(boxPass)){DrawBox(boxPass); HandleTextInput(g_User.passwordLogin, 415, 445);}

    if(ControlMouse(boxLeftBot)){DrawBox(boxLeftBot);} 
    if(ControlMouse(boxMiddleBot)){DrawBox(boxMiddleBot);} 
    esat::DrawSetFillColor(255, 255, 255);
    if(ControlMouse(boxLeftBot) && esat::MouseButtonDown(0)){startScreen_=true; adminIdentify_=false;}

    //Draw again to keep the text in screen
    esat::DrawText(415, 350, g_User.userNameLogin);
    esat::DrawText(415, 445, g_User.passwordLogin);

    esat::DrawSetFillColor(255, 255, 255);
    esat::DrawText(130, 670, "Back");
    esat::DrawText(430, 670, "Confirm");

    if(strcmp(adminReg, g_User.userNameLogin) == 0 && strcmp(adminPas, g_User.passwordLogin) == 0){
        validUserAdmin=true;
    }

    if(validUserAdmin && ControlMouse(boxMiddleBot) && esat::MouseButtonDown(0)){
        admin_ = true;
        register_=false;
        adminIdentify_=false;
        adminBack=true;
        validUserAdmin=false;
    }

}

void RegisterUser(){

    if(deleteText){
        strcpy(g_User.userNameRegister, "");
        strcpy(g_User.passwordRegister, "");
        strcpy(g_User.name, "");
        strcpy(g_User.birthDate, "");
        strcpy(g_User.province, "");
        strcpy(g_User.country, "");
        strcpy(g_User.email, "");
        strcpy(g_User.email2, "");
        deleteText=false;
    }

    esat::DrawSetTextFont("./resources/font/fontV2.ttf");
	esat::DrawSetTextSize(30.0f);
	esat::DrawSetFillColor(255, 255, 255);

    esat::DrawText(100, 200, "Name & surname:");
    esat::DrawText(100, 250, "Date of birth:");
    esat::DrawText(100, 300, "Province:");
    esat::DrawText(100, 350, "Country:");
    esat::DrawText(100, 400, "Username:");
    esat::DrawText(100, 450, "Password:");
    esat::DrawText(100, 500, "Email:");
    esat::DrawText(100, 550, "Credits:");


    if(ControlMouse(bClear) && esat::MouseButtonDown(0)){
        strcpy(g_User.userNameRegister, "");
        strcpy(g_User.passwordRegister, "");
        strcpy(g_User.name, "");
        strcpy(g_User.birthDate, "");
        strcpy(g_User.province, "");
        strcpy(g_User.country, "");
        strcpy(g_User.email, "");
        strcpy(g_User.email2, "");
    }

    //Black box is allways drawn
	DrawBlackBox(bReg1);
    DrawBlackBox(bReg2);
    DrawBlackBox(bReg3);
    DrawBlackBox(bReg4);
    DrawBlackBox(bReg5);
    DrawBlackBox(bReg6);
    DrawBlackBox(bReg7);
    DrawBlackBox(bReg8);
    DrawBlackBox(boxMiddleBot);
    DrawBlackBox(bClear);

    esat::DrawSetTextSize(40.0f);
    if(ControlMouse(boxLeftBot)){DrawBox(boxLeftBot);} else{DrawBlackBox(boxLeftBot);}

    //Write text and draw blue box
    if(ControlMouse(bReg1)){DrawBox(bReg1); HandleTextInput(g_User.name, 360, 196);}
    if(ControlMouse(bReg2)){DrawBox(bReg2); HandleTextInput(g_User.birthDate, 360, 246);}
    if(ControlMouse(bReg3)){DrawBox(bReg3); HandleTextInput(g_User.province, 360, 296);}
    if(ControlMouse(bReg4)){DrawBox(bReg4); HandleTextInput(g_User.country, 360, 346);}
    if(ControlMouse(bReg5)){DrawBox(bReg5); HandleTextInput(g_User.userNameRegister, 360, 396);}
    if(ControlMouse(bReg6)){DrawBox(bReg6); HandleTextInput(g_User.passwordRegister, 360, 446);}
    if(ControlMouse(bReg7)){DrawBox(bReg7); HandleTextInput(g_User.email, 360, 496);}
    if(ControlMouse(bReg8)){DrawBox(bReg8); HandleTextInput(g_User.email2, 677, 496);}
    if(ControlMouse(boxMiddleBot)){DrawBox(boxMiddleBot);}
    if(ControlMouse(bClear)){DrawBox(bClear);}

    esat::DrawSetFillColor(255, 255, 255);
    //Draw again to keep the text in screen
    esat::DrawText(360, 196, g_User.name);
    esat::DrawText(360, 246, g_User.birthDate);
    esat::DrawText(360, 296, g_User.province);
    esat::DrawText(360, 346, g_User.country);
    esat::DrawText(360, 396, g_User.userNameRegister);
    esat::DrawText(360, 446, g_User.passwordRegister);
    esat::DrawText(360, 496, g_User.email);
    esat::DrawText(677, 496, g_User.email2);

    if(ControlMouse(boxLeftBot) && esat::MouseButtonDown(0)){startScreen_=true; register_=false;}
    if(adminBack && ControlMouse(boxLeftBot) && esat::MouseButtonDown(0)){admin_=true; register_=false;}

    esat::DrawText(130, 670, "Back");
    esat::DrawText(650, 495, "@");
    esat::DrawText(350, 545, "10");
    esat::DrawText(430, 670, "Confirm");
    esat::DrawSetTextSize(30.0f);
    esat::DrawText(1062, 495, "Clear");
    
}

void DeleteUser(){
    int cont=0, ret;

    if(ControlMouse(bDelete) && esat::MouseButtonDown(0)){deleteRecord=1;}
    if(ControlMouse(bDelete2) && esat::MouseButtonDown(0)){deleteRecord=2;}
    if(ControlMouse(bDelete3) && esat::MouseButtonDown(0)){deleteRecord=3;}
    if(ControlMouse(bDelete4) && esat::MouseButtonDown(0)){deleteRecord=4;}
    if(ControlMouse(bDelete5) && esat::MouseButtonDown(0)){deleteRecord=5;}
    if(ControlMouse(bDelete6) && esat::MouseButtonDown(0)){deleteRecord=6;}
    if(ControlMouse(bDelete7) && esat::MouseButtonDown(0)){deleteRecord=7;}
    if(ControlMouse(bDelete8) && esat::MouseButtonDown(0)){deleteRecord=8;}

    if(deleteRecord > 0){
        oldname = "UserData.dat"; 
        newname= "UserData_2.dat";

        ret = rename(oldname, newname);

        if(ret != 0) {printf("Error: unable to rename the file");}

        fSave_2 = fopen("UserData_2.dat", "rb");
        if(fSave_2 == nullptr){
            return;
        }
        
        while(fread(g_User.userNameRegister, sizeof(char), 20, fSave_2) != 0){
            
            cont++;
            fread(g_User.userMaxScore,sizeof(int),1,fSave_2);
            fread(g_User.passwordRegister, sizeof(char), 20, fSave_2);
            fread(g_User.name, sizeof(char), 20, fSave_2);
            fread(g_User.birthDate, sizeof(char), 20, fSave_2);
            fread(g_User.province, sizeof(char), 20, fSave_2);
            fread(g_User.country, sizeof(char), 20, fSave_2);
            fread(g_User.email, sizeof(char), 13, fSave_2);
            fread(g_User.email2, sizeof(char), 14, fSave_2);

            if(cont != deleteRecord){
                fSave=fopen("UserData.dat", "ab");

                fwrite(g_User.userNameRegister, sizeof(char), 20, fSave);
                fwrite(&score, sizeof(int),1, fSave);
                fwrite(g_User.passwordRegister, sizeof(char), 20, fSave);
                fwrite(g_User.name, sizeof(char), 20, fSave);
                fwrite(g_User.birthDate, sizeof(char), 20, fSave);
                fwrite(g_User.province, sizeof(char), 20, fSave);
                fwrite(g_User.country, sizeof(char), 20, fSave);
                fwrite(g_User.email, sizeof(char), 13, fSave);
                fwrite(g_User.email2, sizeof(char), 14, fSave);

                fclose(fSave);
            }
        }
        deleteRecord = 0;
        fclose(fSave_2);

        ret = remove(newname);
        if(ret != 0) {printf("Error in deleting file\n");}
    }  
}

void LoadEditUser(){

    if(ControlMouse(bEdit) && esat::MouseButtonDown(0)){editRecord=1;}
    if(ControlMouse(bEdit2) && esat::MouseButtonDown(0)){editRecord=2;}
    if(ControlMouse(bEdit3) && esat::MouseButtonDown(0)){editRecord=3;}
    if(ControlMouse(bEdit4) && esat::MouseButtonDown(0)){editRecord=4;}
    if(ControlMouse(bEdit5) && esat::MouseButtonDown(0)){editRecord=5;}
    if(ControlMouse(bEdit6) && esat::MouseButtonDown(0)){editRecord=6;}
    if(ControlMouse(bEdit7) && esat::MouseButtonDown(0)){editRecord=7;}
    if(ControlMouse(bEdit8) && esat::MouseButtonDown(0)){editRecord=8;}

    if(editRecord > 0){

        fSave = fopen("UserData.dat", "r+b");
        if(fSave == nullptr){
            return;
        }

        while(fread(g_User.userNameRegister, sizeof(char), 20, fSave) != 0){
            contEdit++;

            fread(g_User.userMaxScore,sizeof(int),1,fSave);
            fread(g_User.passwordRegister, sizeof(char), 20, fSave);
            fread(g_User.name, sizeof(char), 20, fSave);
            fread(g_User.birthDate, sizeof(char), 20, fSave);
            fread(g_User.province, sizeof(char), 20, fSave);
            fread(g_User.country, sizeof(char), 20, fSave);
            fread(g_User.email, sizeof(char), 13, fSave);
            fread(g_User.email2, sizeof(char), 14, fSave);  

            if(contEdit == editRecord){
                register_=true;
                admin_=false;
                break;
            }
        }

        fclose(fSave);
        editRecord = 0;
    }
}

void UpdateUser(){
    //if edit button is pressed, change data
    int cont=0;

    fSave = fopen("UserData.dat", "r+b");
    if(fSave == nullptr){
        return;
    }

    while(fread(var20, sizeof(char), 20, fSave) != 0){
        cont++;

        if(cont == contEdit){
            fseek(fSave, -20*sizeof(char), SEEK_CUR);
            fwrite(g_User.userNameRegister, sizeof(char), 20, fSave);
        }

        fread(g_User.userMaxScore,sizeof(int),1,fSave);
        fread(var20, sizeof(char), 20, fSave);
        if(cont == contEdit){
            fseek(fSave, -20*sizeof(char), SEEK_CUR);
            fwrite(g_User.passwordRegister, sizeof(char), 20, fSave);
        }

        fread(var20, sizeof(char), 20, fSave);
        if(cont == contEdit){
            fseek(fSave, -20*sizeof(char), SEEK_CUR);
            fwrite(g_User.name, sizeof(char), 20, fSave);
        }

        fread(var20, sizeof(char), 20, fSave);
        if(cont == contEdit){
            fseek(fSave, -20*sizeof(char), SEEK_CUR);
            fwrite(g_User.birthDate, sizeof(char), 20, fSave);
        }

        fread(var20, sizeof(char), 20, fSave);
        if(cont == contEdit){
            fseek(fSave, -20*sizeof(char), SEEK_CUR);
            fwrite(g_User.province, sizeof(char), 20, fSave);
        }

        fread(var20, sizeof(char), 20, fSave);
        if(cont == contEdit){
            fseek(fSave, -20*sizeof(char), SEEK_CUR);
            fwrite(g_User.country, sizeof(char), 20, fSave);
        }

        fread(var13, sizeof(char), 13, fSave);
        if(cont == contEdit){
            fseek(fSave, -13*sizeof(char), SEEK_CUR);
            fwrite(g_User.email, sizeof(char), 13, fSave);
        }

        fread(var14, sizeof(char), 14, fSave); 
        if(cont == contEdit){
            fseek(fSave, -14*sizeof(char), SEEK_CUR);
            fwrite(g_User.email2, sizeof(char), 14, fSave);
            break;
        }
    }

    if(ControlMouse(boxMiddleBot) && esat::MouseButtonDown(0) || ControlMouse(boxLeftBot) && esat::MouseButtonDown(0)){
        contEdit=0;
        admin_=true;
        register_=false;
    }

    fclose(fSave);
}

void ListUsers(){

    int cont=0;

    esat::DrawSetFillColor(35, 82, 176);
    esat::DrawSetTextSize(12.0f);
    esat::DrawSetTextFont("./resources/font/fontV3.ttf");
    esat::DrawText(50, 160, "Username");
    esat::DrawText(206, 160, "Name/Surname");
    esat::DrawText(387, 160, "birth date");
    esat::DrawText(537, 160, "province");
    esat::DrawText(678, 160, "Country");
    esat::DrawText(880, 160, "email");

    for(int i=150; i<=565; i+=5){
        esat::DrawText(175, i, "|");
        esat::DrawText(376, i, "|");
        esat::DrawText(505, i, "|");
        esat::DrawText(657, i, "|");
        esat::DrawText(775, i, "|");
        esat::DrawText(1040, i, "|");
    }

    for(int i=10; i<=1180; i+=5){
        esat::DrawText(i, 145, "-");
        esat::DrawText(i, 575, "-");
        esat::DrawText(i, 175, "-");
    }

    
    esat::DrawSetTextSize(40.0f);
    esat::DrawSetFillColor(255, 255, 255);
    esat::DrawText(40, 60, "list of users");
    esat::DrawText(0, 100, "------------------------------------------");
    esat::DrawSetTextFont("./resources/font/fontV2.ttf");
    esat::DrawSetTextSize(40.0f);
    esat::DrawSetFillColor(255, 255, 255);

    //------------
    DrawBlackBox(boxLeftBot);
    if(ControlMouse(boxLeftBot)){DrawBox(boxLeftBot);}
    //------------

    //---------------------------
    DrawBlackBox(bEdit); DrawBlackBox(bDelete);                    
    DrawBlackBox(bEdit2); DrawBlackBox(bDelete2);           
    DrawBlackBox(bEdit3); DrawBlackBox(bDelete3);           
    DrawBlackBox(bEdit4); DrawBlackBox(bDelete4);           
    DrawBlackBox(bEdit5); DrawBlackBox(bDelete5);           
    DrawBlackBox(bEdit6); DrawBlackBox(bDelete6);           
    DrawBlackBox(bEdit7); DrawBlackBox(bDelete7);           
    DrawBlackBox(bEdit8); DrawBlackBox(bDelete8);           
    //---------------------------

    if(ControlMouse(boxLeftBot) && esat::MouseButtonDown(0)){startScreen_=true; admin_=false;}
    if(ControlMouse(boxRightBot) && esat::MouseButtonDown(0) && admin_){
        register_=true;
        admin_=false;
        deleteText=true;
    }

    esat::DrawSetFillColor(255, 255, 255);
    esat::DrawText(130, 670, "Back");
    

    FILE* fSave = fopen("UserData.dat", "rb");
    if(fSave == nullptr){
        return;
    }

    //Set the initial position of the first score to display
    int x = 35;
    int y = 200;
    esat::DrawSetTextSize(20.0f);

    while(fread(g_User.userNameRegister, sizeof(char), 20, fSave) != 0){

        fread(g_User.userMaxScore,sizeof(int),1,fSave);
        fread(g_User.passwordRegister, sizeof(char), 20, fSave);
        fread(g_User.name, sizeof(char), 20, fSave);
        fread(g_User.birthDate, sizeof(char), 20, fSave);
        fread(g_User.province, sizeof(char), 20, fSave);
        fread(g_User.country, sizeof(char), 20, fSave);
        fread(g_User.email, sizeof(char), 13, fSave);
        fread(g_User.email2, sizeof(char), 14, fSave);

        cont++;

        esat::DrawText(x, y, g_User.userNameRegister);
        esat::DrawText(x + 150, y, g_User.name);
        esat::DrawText(x + 350, y, g_User.birthDate);
        esat::DrawText(x + 484, y, g_User.province);
        esat::DrawText(x + 634, y, g_User.country);
        esat::DrawText(x + 750, y, g_User.email);
        esat::DrawText(x + 885, y, "@");
        esat::DrawText(x + 900, y, g_User.email2);

        esat::DrawSetFillColor(255, 255, 255);
        for(int j=0; j<cont; j++){

            
            if(ControlMouse(bEdit) && cont==1){DrawBox(bEdit);}              
            if(ControlMouse(bEdit2) && cont==2){DrawBox(bEdit2);}               
            if(ControlMouse(bEdit3) && cont==3){DrawBox(bEdit3);}      
            if(ControlMouse(bEdit4) && cont==4){DrawBox(bEdit4);}               
            if(ControlMouse(bEdit5) && cont==5){DrawBox(bEdit5);}               
            if(ControlMouse(bEdit6) && cont==6){DrawBox(bEdit6);}               
            if(ControlMouse(bEdit7) && cont==7){DrawBox(bEdit7);}               
            if(ControlMouse(bEdit8) && cont==8){DrawBox(bEdit8);}   

            if(ControlMouse(bDelete) && cont==1){DrawBox(bDelete);}
            if(ControlMouse(bDelete2) && cont==2){DrawBox(bDelete2);}
            if(ControlMouse(bDelete3) && cont==3){DrawBox(bDelete3);}
            if(ControlMouse(bDelete4) && cont==4){DrawBox(bDelete4);}
            if(ControlMouse(bDelete5) && cont==5){DrawBox(bDelete5);}
            if(ControlMouse(bDelete6) && cont==6){DrawBox(bDelete6);}
            if(ControlMouse(bDelete7) && cont==7){DrawBox(bDelete7);}
            if(ControlMouse(bDelete8) && cont==8){DrawBox(bDelete8);}            

            esat::DrawSetFillColor(255, 255, 255);
            esat::DrawText(1070, y, "Edit");
            esat::DrawText(1123, y, "Delete");
        }

        y += 50;
    }
    fclose(fSave);
}

void ControlsInfo(){
    esat::DrawSetTextFont("./resources/font/fontV3.ttf");
	esat::DrawSetTextSize(25.0f);
	esat::DrawSetFillColor(255, 255, 255);

    esat::DrawSprite(p, 90, 60);
    esat::DrawText(190, 130, " TO PAUSE");

    esat::DrawSprite(arrows, 90, 245);
    esat::DrawText(150, 500, "Movement");

    esat::DrawSprite(g, 500, 320);
    esat::DrawText(465, 500, "Hyperspace");

    esat::DrawSprite(spacekey, 750, 320);
    esat::DrawText(850, 500, "Shoot");

    DrawBlackBox(boxLeftBot);
    if(ControlMouse(boxLeftBot)){DrawBox(boxLeftBot);} 

    if(ControlMouse(boxLeftBot) && esat::MouseButtonDown(0)){back_=true;}

    esat::DrawSetFillColor(255, 255, 255);
    esat::DrawSetTextSize(40.0f);
    esat::DrawSetTextFont("./resources/font/fontV2.ttf");
    esat::DrawText(130, 670, "Back");
}

void UpdateScore(){
    fSave = fopen("UserData.dat", "r+b");
    if(fSave == nullptr){
        return;
    }

    maxScore = score;

    while(fread(g_User.userNameRegister, sizeof(char), 20, fSave) != 0){

        fread(&score,sizeof(int),1,fSave);
        if(strcmp(g_User.userNameRegister, g_User.userNameLogin) == 0){

            fseek(fSave, -1*sizeof(int), SEEK_CUR);
            fwrite(&maxScore, sizeof(int),1,fSave);
            break;
        }      

        fread(g_User.passwordRegister, sizeof(char), 20, fSave);
        fread(g_User.name, sizeof(char), 20, fSave);
        fread(g_User.birthDate, sizeof(char), 20, fSave);
        fread(g_User.province, sizeof(char), 20, fSave);
        fread(g_User.country, sizeof(char), 20, fSave);
        fread(g_User.email, sizeof(char), 13, fSave);
        fread(g_User.email2, sizeof(char), 14, fSave);  
    }
    fclose(fSave);
}

void UIGame(){
   char *pointsChain = new char, *maxScoreChain = new char, *timerChain = new char;;
   int i=score, j=maxScore, k=startTime;

   itoa(i, pointsChain, 10);
   itoa(j, maxScoreChain, 10);
   itoa(k, timerChain, 10);

   esat::DrawSetTextFont("./resources/font/font.ttf");
   esat::DrawSetFillColor(255,255,255);
   if(colorMode){
      esat::DrawSetFillColor(138,43,226);
    }
   esat::DrawSetTextSize(40.0f);
   esat::DrawText(50, 40, pointsChain);
   esat::DrawText(50, 40, pointsChain);
   esat::DrawText(50, 40, pointsChain);

   esat::DrawSetTextSize(30.0f);
   esat::DrawText(582, 40, maxScoreChain);
   esat::DrawText(582, 40, maxScoreChain);
   esat::DrawText(582, 40, maxScoreChain);
   
   esat::DrawSetTextFont("./resources/font/font.ttf"); 
   
   if(timerMode){ //Timer mode, starts at 90 secs
        if(!isGamePaused){
            startTime = startTime - 0.015; 

            if((int)startTime == 0 && !isPlayerDead){
                DetectSoundPlayerDead=true;
                playerLife = 0;
                isPlayerDead = true;
            }   
            if((int)startTime == 0){startTime = 0;}

            minutes = (int)startTime / 60;
            seconds = (int)startTime % 60;
        }
        sprintf(timerChain, "%02d:%02d", (int)minutes, (int)seconds);

      esat::DrawSetTextSize(50.0f);
      esat::DrawText(1000, 50, timerChain);
      esat::DrawText(1000, 50, timerChain);
      esat::DrawText(1000, 50, timerChain);
      esat::DrawSetTextSize(40.0f);
   }else{
        switch(playerLife){
         //case 4: esat::DrawSprite(ship, 50, 45); esat::DrawSprite(ship, 80, 45); esat::DrawSprite(ship, 110, 45); break;
         case 3: esat::DrawSprite(ship, 50, 45); esat::DrawSprite(ship, 80, 45); esat::DrawSprite(ship, 110, 45); break;
         case 2: esat::DrawSprite(ship, 50, 45); esat::DrawSprite(ship, 80, 45); break;
         case 1: esat::DrawSprite(ship, 50, 45); break;
        }
    }

    if(playerLife < 1){
        
        DrawBlackBox(box1);
        DrawBlackBox(box2);
        if(ControlMouse(box1)){DrawBox(box1);} 
        if(ControlMouse(box2)){DrawBox(box2);}

        esat::DrawSetTextSize(80.0f);
        esat::DrawSetFillColor(255, 255, 255);
        if(colorMode){
            esat::DrawSetFillColor(138,43,226);
        }
        esat::DrawText(360, 300, "GAME OVER");

        esat::DrawSetFillColor(255, 255, 255);
        esat::DrawSetTextSize(40.0f);
        esat::DrawText(100, 420, "Play again");
        esat::DrawText(100, 420, "Play again");
        esat::DrawText(100, 420, "Play again");
        esat::DrawText(825, 420, "Main Menu");
        esat::DrawText(825, 420, "Main Menu");
        esat::DrawText(825, 420, "Main Menu");

        g_Player->position.y = 1200;

        gameEnd=true;
    
        //Save player score if game over and score is higher than max score
        if(score > maxScore){
            UpdateScore();
        }
    }

    free(pointsChain);
    free(maxScoreChain);
}

void ShowHighScores(){

    if(colorMode){
        esat::DrawSetStrokeColor(0,255,255);
    }else{
        esat::DrawSetStrokeColor(255, 255, 255);
    }
    
    TransformAndDraw(triangle_coords, 40.0f, esat::Time()*0.003, 70.0f, 60.0f, transformed_Triangle, 3);
    TransformAndDraw(triangle_coords, 40.0f, esat::Time()*0.003, 1130.0f, 60.0f, transformed_Triangle, 3);
    
    char *showScoreChain = new char, *tempUser = new char;
    int cont = 0, tempScore, num=0;

    esat::DrawSetTextFont("./resources/font/fontV3.ttf");
    esat::DrawSetTextSize(70.0f);
    esat::DrawText(235, 100, "High Scores");
    
    esat::DrawSetTextFont("./resources/font/fontV2.ttf");
    esat::DrawSetTextSize(40.0f);

    FILE* fSave = fopen("UserData.dat", "rb");
    if(fSave == nullptr){
        return;
    }

    // Set the initial position of the first score to display
    int x = 310;
    int y = 200;

    esat::DrawSetStrokeColor(255, 255, 255);
    //Read and display the top 10 highest scores
    while(fread(g_User.userNameRegister, sizeof(char), 20, fSave) != 0){
        
        strcpy((g_OrderedUsers + cont)->userNameRegisterOrdered, g_User.userNameRegister);
        fread(g_User.userMaxScore,sizeof(int),1,fSave);
        (g_OrderedUsers + cont)->userMaxScoreOrdered = *g_User.userMaxScore;

        fread(g_User.passwordRegister, sizeof(char), 20, fSave);
        fread(g_User.name, sizeof(char), 20, fSave);
        fread(g_User.birthDate, sizeof(char), 20, fSave);
        fread(g_User.province, sizeof(char), 20, fSave);
        fread(g_User.country, sizeof(char), 20, fSave);
        fread(g_User.email, sizeof(char), 13, fSave);
        fread(g_User.email2, sizeof(char), 14, fSave);
        cont++;
    }

    //Order users of maxScores using bubble algorithm
    for(int i=0; i<cont; i++){
        for(int j=0; j<(cont-i-1); j++){
            if((g_OrderedUsers+j)->userMaxScoreOrdered < (g_OrderedUsers+j+1)->userMaxScoreOrdered) {

               tempScore = (g_OrderedUsers + j)->userMaxScoreOrdered;
               (g_OrderedUsers + j)->userMaxScoreOrdered = (g_OrderedUsers + j + 1)->userMaxScoreOrdered;
               (g_OrderedUsers + j + 1)->userMaxScoreOrdered = tempScore;

               strcpy(tempUser, (g_OrderedUsers + j)->userNameRegisterOrdered);
                strcpy((g_OrderedUsers + j)->userNameRegisterOrdered, (g_OrderedUsers + j + 1)->userNameRegisterOrdered);
                strcpy((g_OrderedUsers + j + 1)->userNameRegisterOrdered, tempUser);
            }
        }
    }
    //print ordered scores
    for(int i=0; i<cont; i++){

        itoa((g_OrderedUsers + i)->userMaxScoreOrdered, showScoreChain, 10);
        esat::DrawText(x, y, (g_OrderedUsers + i)->userNameRegisterOrdered);
        esat::DrawText(x + 510, y, showScoreChain);
        y += 60;
    }

    fclose(fSave);
    free(showScoreChain);
    free(tempUser);
}

void PauseGame(){
    if(esat::IsKeyDown('P')){
        isGamePaused = !isGamePaused;
    }

    if(isGamePaused && boolLoad==false){

        UIGame();
        
        float *p=(float*)malloc(10*sizeof(float));
        *(p+0) = 100;
        *(p+1) = 100;
        *(p+2) = 100 + 1000;
        *(p+3) = 100;
        *(p+4) = 100 + 1000;
        *(p+5) = 100 + 600;
        *(p+6) = 100;
        *(p+7) = 100 + 600;
        *(p+8) = *(p+0);
        *(p+9) = *(p+1);
        esat::DrawSetFillColor(0, 0, 0);
        esat::DrawSolidPath(p, 5);

        DrawBlackBox(bPause);
        if(ControlMouse(bPause)){DrawBox(bPause);} 
        TransformAndDraw(triangle_coords, 40.0f, esat::Time()*0.003, 150.0f, 150.0f, transformed_Triangle, 3);
        TransformAndDraw(triangle_coords, 40.0f, esat::Time()*0.003, 1040.0f, 150.0f, transformed_Triangle, 3);

        esat::DrawSetTextFont("./resources/font/fontV3.ttf");
        esat::DrawSetTextSize(70.0f);
        esat::DrawSetFillColor(255, 255, 255);
        if(colorMode){
            esat::DrawSetFillColor(138,43,226);
        }
        esat::DrawText(230, 270, "GAME PAUSED");
        esat::DrawSetTextSize(20.0f);
        esat::DrawText(115, 690, "P TO RESUME");

        esat::DrawSetTextFont("./resources/font/font.ttf");
        esat::DrawSetTextSize(70.0f);
        esat::DrawText(405, 450, "MAIN MENU");
        esat::DrawText(405, 450, "MAIN MENU");
        esat::DrawText(405, 450, "MAIN MENU");

        //Reset all variables
        if(ControlMouse(bPause) && esat::MouseButtonDown(0)){
           esat::ResetBufferdKeyInput();
           isGamePaused=false;
            numEnemies = 4;
            score = 0;
            InitPlayer();
            InitBullet();
            InitBulletUFO();
            InitSprites();
            InitAsteroid();
            InitUFO();
            InitShapeCoords(triangle_coords, 3);
            InitShapeCoords(circle_coords, 30);

            g_UFO.active = false;
            gamestart = false;
            gameEnd = false;
            identify_=false;
            register_ = false;
            registerin = true; 
            identifyin = true; 
            back_ = false; 
            play_ = false;
            controlsinfo_ = false;
            immortalStart = true;
            boolLoad=true;
            countLoad=0;
            playerLife = 3;
            numEnemies = 4;
            score = 0;
            maxScore = maxScore;
            countInitAsteroids = 4;

            if(timerMode){
                startTime = 90;  
                minutes=0;
                seconds=0;
                isPlayerDead=false;
            }
        }
        free(p);
    }
}

void ColorMode(){

    DrawBlackBox(boxMiddleBot);

    if(ControlMouse(boxMiddleBot) && esat::MouseButtonDown(0)){
        colorMode = !colorMode;
    }
    esat::DrawSetTextSize(25.0f);
    esat::DrawSetTextFont("./resources/font/fontV3.ttf");
    esat::DrawText(390, 740, "Color mode");
    esat::DrawSetTextSize(50.0f);
    esat::DrawSetFillColor(0,255,0);
    if(colorMode){esat::DrawText(452, 680, "ON");}
    esat::DrawSetFillColor(255,0,0);
    if(!colorMode){esat::DrawText(430, 680, "OFF");}
    esat::DrawSetFillColor(255,255,255);
}

void TimeMode(){
    DrawBlackBox(boxMiddleBot2);

    if(ControlMouse(boxMiddleBot2) && esat::MouseButtonDown(0)){
        timerMode = !timerMode;
    }
    esat::DrawSetTextSize(25.0f);
    esat::DrawSetTextFont("./resources/font/fontV3.ttf");
    esat::DrawText(650, 740, "Timer mode");
    esat::DrawSetTextSize(50.0f);
    esat::DrawSetFillColor(0,255,0);
    if(timerMode){esat::DrawText(722, 680, "ON");}
    esat::DrawSetFillColor(255,0,0);
    if(!timerMode){esat::DrawText(700, 680, "OFF");}
    esat::DrawSetFillColor(255,255,255);
}

void MarioMode(){    

    float *shape = (float*)malloc(16 * 2 * sizeof(float));
    *(shape + 0) = 0.0f;
    *(shape + 1) = 0.0f;        *(shape + 3) = 3.0f;
    *(shape + 2) = 0.0f;        *(shape + 4) = 1.0f;

    *(shape + 5) = 4.0f;        *(shape + 7) = 4.0f;
    *(shape + 6) = 7.0f;        *(shape + 8) = 8.0f;

    *(shape + 9) = 3.0f;        *(shape + 11) = -1.0f;
    *(shape + 10) = 8.0f;       *(shape + 12) = 7.0f;

    *(shape + 13) = -2.0f;      *(shape + 15) = -2.0f;
    *(shape + 14) = 5.0f;       *(shape + 16) = 5.0f;

    *(shape + 17) = -4.0f;      *(shape + 19) = -4.0f;
    *(shape + 18) = 3.0f;       *(shape + 20) = 3.0f;

    *(shape + 21) = -1.0f;      *(shape + 23) = 0.0f;
    *(shape + 22) = 4.0f;       *(shape + 24) = 6.0f;

    *(shape + 25) = 0.0f;       *(shape + 27) = 2.0f;
    *(shape + 26) = 6.0f;       *(shape + 28) = 2.0f;

    *(shape + 29) = 2.0f;       *(shape + 31) = 0.0f;
    *(shape + 30) = 2.0f;


    DrawBlackBox(boxMiddleBot3);
    if(ControlMouse(boxMiddleBot3) && esat::MouseButtonDown(0)){
       MBmode = !MBmode; 
       DetectSoundCoin=true;
    }

    if(MBmode){
        esat::DrawSetStrokeColor(251, 208, 0);
	    esat::DrawSetFillColor(251, 208, 0);
    }else{
        esat::DrawSetStrokeColor(255, 255, 255);
	    esat::DrawSetFillColor(0, 0, 0);
    }   

    esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(10.0f, 10.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(PI), m);
    m = esat::Mat3Multiply(esat::Mat3Scale(-1.0f, 1.0f), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(1015, 650),m);

    float *transformed_Inter = (float*)malloc(32 * sizeof(float));

	for (int i = 0; i < 16; ++i) {
        esat::Vec3 p = { *(shape + i * 2), *(shape + i * 2 + 1), 1.0f };
        esat::Vec3 result = esat::Mat3TransformVec3(m, p);
        *(transformed_Inter + i * 2) = result.x;
        *(transformed_Inter + i * 2 + 1) = result.y;
    }
	esat::DrawSolidPath(transformed_Inter, 16);

    TransformAndDraw(circle_coords, 6.0f, 0.0f, 995.0f, 605.0f, transformed_Circle, 30);
    TransformAndDraw(circle_coords, 6.0f, 0.0f, 1115.0f, 605.0f, transformed_Circle, 30);
    TransformAndDraw(circle_coords, 6.0f, 0.0f, 995.0f, 715.0f, transformed_Circle, 30);
    TransformAndDraw(circle_coords, 6.0f, 0.0f, 1115.0f, 715.0f, transformed_Circle, 30);

    float *p=(float*)malloc(10*sizeof(float));
    *(p+0) = 1045;
    *(p+1) = 700;
    *(p+2) = 1045 + 20;
    *(p+3) = 700;
    *(p+4) = 1045 + 20;
    *(p+5) = 700 + 20;
    *(p+6) = 1045;
    *(p+7) = 700 + 20;
    *(p+8) = *(p+0);
    *(p+9) = *(p+1);
    
    if(!MBmode){esat::DrawSetFillColor(0, 0, 0);}else{esat::DrawSetFillColor(251, 208, 0);}
    
    esat::DrawSolidPath(p, 5);

    free(p);
    free(shape);
    free(transformed_Inter);
}









