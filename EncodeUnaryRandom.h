


//***************************** ENCODING ********************************
void EncodeUnaryRandom(std::string& InputBytes)
{
    unsigned int Previous_bufindex = 0, NumberOfUnaryBits = 0, i = 0, j = 0, k = 0, Bit_Index_For_Byte = 0, ii = 0, Kbytes = 0;
    unsigned int OriginalVArray[400], OriginalRArray[400], RandIndex[400], VArray[400], RArray[400], SizeChunk[400], ShuffleArray[400][2];
  
    unsigned int Total_Bits = 0, BitCount = 0, kk = 0, BitsLeft, firstone = 0, Size = 0;
    unsigned  int BytesFromInputLoop = 0, NumberBytes = 0, NumberBits = 0, size=0;
    unsigned char xin = 0, XinLow = 0, XinHigh = 0, alternate = 0;
    unsigned int ctemp = 0, R = 0, tempscheme = 0;
    unsigned int v1 = 0, v2 = 0, r1 = 0, r2 = 0, PlainTextMemorySize = 0, NumberOfPlainTextBits = 0, ArrayIndex = 0, rtemp = 0, V = 0, BitsEncoded = 0;
    unsigned int ChunkSize = 0, ChunkCount = 0, NewChunkSize = 0;
    //
    unsigned char Left_Over = 0, ByteTemp = 0, NextByte = 0, CharTemp = 0, vtemp=0,Random = 0;
    unsigned char PreviousNull = 1,temp = 0, Alternate = 0, AddNulls = 0x00;
    unsigned char Mask[8];
    unsigned char DecodeMask = 0;
    
    bool TestBit, One = 1, TempTest = 0, Vstart = 0,SwapChunks=0,krandom=0,XorBits=0;
    //**************************************************** Trailer ************************
    unsigned int TrailerLength = 24;
    std::bitset<4>Nulls1("0011");
    std::bitset<4>Nulls0("1100");
    std::string ConsoleInput;
    std::string TempString;
    //***************************************** Bits *************************
    std::bitset<5000>PlainTextBiits; // the max for sum of vs and rs are 512
    PlainTextMemorySize = PlainTextBiits.size();
    std::bitset<10000>EncodedBits;
    std::bitset<256>ChunkBits;// largest chunk would be this size
    std::bitset<10000>DecodedBits;
    std::bitset <8>TempBits;
    std::bitset <10000>EncryptBits;
    //********************************************************************
    std::cout << "\n        Random Swap Chunks ? .... Enter Y or N  ";
    std::cin >> TempString;
    std::cout << " \n";

    SwapChunks = 1;
    if(TempString=="N")SwapChunks = 0;
    if (TempString == "n")SwapChunks = 0;
    
    std::cout << "\n        Encrypt Meaage with XOR ? .... Enter Y or N  ";
    std::cin >> TempString;
    std::cout << " \n";
    XorBits = 1;
    if (TempString == "N")XorBits = 0;
        if (TempString == "n")XorBits = 0;
  
   
   for (i = 0;i < 400;i++)
    {
        VArray[i] = 0;RArray[i] = 0;
    }
    EncryptBits.reset();
    srand;
    for (i = 0;i < 10000;i++)
    {
        j = rand()% 2;
        
        if(j==1) EncryptBits.flip(i);
    }
    ConsoleInput = "";
   
  
    //*******************************************
    NumberBytes = InputBytes.size();
    BytesFromInputLoop = 0;

    std::cout << "      Enter Chunk SIze .. 0 for random  ";
    std::cin >> ChunkSize;

    if (ChunkSize == 0) Random = 1;

    if (Random == 1) {
        ChunkSize = rand() % 5 + 3;
    }

    std::cout << " Chunk Size " << ChunkSize << "\n";


    CharTemp = 0;
    temp = 0b10000000;
    for (i = 0;i < 8;i++) {

        Mask[i] = temp;
        temp >>= 1;
    }
    // Convert Bytes into a plaint text BitStream ***************************************
    std::cout << "  Convert Bytes into a plaint text BitStream *************************************** ";
    kk = NumberBytes;
    NumberOfPlainTextBits = (kk <<= 3);

    BytesFromInputLoop = 0;

    std::cout << " This is the message " << " \n";
    // encode byte message into chunk streams
    while (BytesFromInputLoop < NumberBytes)
    {

        xin = InputBytes[BytesFromInputLoop];// 8 bits read in  
        std::cout << " xin = " << xin << " ";;
        for (i = 0;i < 8;i++)
        {
            TestBit = bool(Mask[i] & xin);
            PlainTextBiits.set(BitCount, TestBit);
            std::cout << TestBit;
            BitCount++;
        }
        BytesFromInputLoop++;
    
    }
    NumberBits = BitCount;
    // FIND OUT HOW MANY LEFT TO FILL A BYTE 

    ArrayIndex = 0;
    BitsLeft = 0;
    std::cout << "\n";
    std::cout << "\n" << NumberBytes << " Bytes in message  " << NumberBytes << "  Number of bits are " << NumberBits << " \n";
    std::cout << "  All bytes are in bits now.Now we will split the Plaintext into chunks \n";

    ChunkCount = 0;// upper bit position
    kk = 0;
    ChunkBits.reset();
    V = 0;
    R = 0;
    //***************************************************************** Now we make a list of the Rs & V's
    for (BitCount = 0;BitCount < NumberBits;BitCount++) {
        // fill of chunk
        // then find how many leading zeros there are
        TestBit = PlainTextBiits.test(BitCount);// MSB TO LSB

        ChunkBits.set(ChunkCount, TestBit);
        ChunkCount++;// KEEP COUNT OF THE NUMBER OF BITS IN THIS CHUNK
        BitsLeft = NumberBits - (BitCount + 1);

        if (ChunkCount == ChunkSize)// count number of zeros
        {
            firstone = 0;
            V = 0;
            R = 0;
            std::cout << " Chunk Size =" << ChunkSize << " ";
            // TestBit was the last bit value
             //*******************************************
            for (i = 0;i < ChunkSize;i++)// llok for first one
            {
                TestBit = ChunkBits.test(i);
                if (firstone == 0)
                {
                    if (TestBit == 1)
                    {
                        firstone = 1;//the rest of the chunk is just the binary value of whats left
                        ii = i;// save position
                    }
                    else
                    {
                        R++;// this counts the leading zeros, 
                    }
                }// working with remander
            };                                 // form an nbit numer
            // the first one is 
            for (j = ii;j < ChunkSize;j++)// FROM THE LSB TO THE FIRST LOCATION
            {

                kk = ChunkBits.test(j);
                kk = (kk << (ChunkSize - j - 1));
                V = kk + V;
            };

            V = V + 1;// add 1 per spec
            R = R + 1;// add 1 per spec
            //Now Put the V and R's intp an array
            OriginalRArray[ArrayIndex] = R;
            OriginalVArray[ArrayIndex] = V;
            ArrayIndex++;

            std::cout << "Original VArray =" << V << "     ";
            std::cout <<"Original RArray = " << R << " ";
            
            //**********************************************
            ChunkCount = 0;
            ChunkBits.reset();

            std::cout << " Remaining bits= " << BitsLeft << " \n";
            if (Random == 1)ChunkSize = rand() % 5 + 3;// between 4 and 12
            //**************** cHECK IF THE NEXT CHUNK ISTOO BIG TO TAKE ALL THE BITS
            if (NewChunkSize == 0) {
                if (BitsLeft > 0) {
                    if (BitsLeft < ChunkSize)// we are at the end and wiill change the chunkSize to include the last bits
                    {

                        ChunkSize = BitsLeft;
                        NewChunkSize = 1;
                        // now we have to encode the BitsLeft 

                    };
                }
            };
        }
        firstone = 0;

    }// This is the Array will all values
    Total_Bits = 0;
    ChunkCount = ArrayIndex;
    for (i = 0;i < ArrayIndex;i++)
    {
        std::cout << "V" << i << "= " << OriginalVArray[i] << " ";
        std::cout << "R" << i << "= " << OriginalRArray[i] << "\n";
    };



    for (i = 0;i < ArrayIndex;i++)  RandIndex[i] = i;
    std::vector<int> nums(RandIndex, RandIndex + ArrayIndex);// CREATE VECTOR TO ENABLE SORTING
    //********************************** C++ Random Sort routine*****************
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(nums.begin(), nums.end(), g);
    //Suffle
    std::cout << " ******************************************THIS IS WHERE WE CAN RANDOMLY SWAP VR CHUNKS *********************************************** \n";
    
    if (!SwapChunks)
    {
        for (i = 0;i <= ChunkCount;i++)
        {
            nums[i]=i;
        }
    }
        //setting up swapping array nums[i];
    std::cout << "\n  VArray   RArray        OriginalVArray      OriginalRArray \n";
        for (int i = 0; i < nums.size(); i++)
        {
            VArray[i] = OriginalVArray[nums[i]];
            RArray[i] = OriginalRArray[nums[i]];
            std::cout << "\n " << i << "  " << VArray[i] << "        " << RArray[i] << "                " << OriginalVArray[i] << "            " << OriginalRArray[i];
            //*******************************************************************************
        }
     std::cout<<"\n";

         NumberOfUnaryBits = 0;
        for (i = 0;i < ArrayIndex;i++) {// RATHER THAN JUST SEQUENTIALLY SEND OUT CHUNKS WE COULD RANDOMLY SEND THEM OUT
            
            kk = VArray[i];
            std::cout << " Chunk Number " << i << " V=  ";
            for (k = 0;k < kk;k++) {
                std::cout << One;
                EncodedBits.set(NumberOfUnaryBits, One);
                NumberOfUnaryBits++;
              
            }
                kk =RArray[i];
                std::cout << " R= ";
                for (k = 0;k < kk;k++) {
                    std::cout << !One;
                    EncodedBits.set(NumberOfUnaryBits, !One);
                    NumberOfUnaryBits++;

                }
                //One = !One;
            
            std::cout << "\n";


        }
        kk = NumberOfUnaryBits;
        i = (kk >>3);// divide by 8 
        k=(i << 3);// bits left over  from bytes
        kk = NumberOfUnaryBits - k;
        TrailerLength =TrailerLength+kk;
        /*
        for (j = 0;j <TrailerLength;j++) {
            
            EncodedBits.set(NumberOfUnaryBits, One);
            NumberOfUnaryBits++;
            //One = !One;
        }
        //Trailer
        */
    
    std::cout << " Number of Bits =" << NumberOfUnaryBits << "\n";

    std::cout << " \n        *****************  This in the final unencrypted  encoded bit stream to be sent over a network *************************************** \n\n\n";
    for (i = 0;i < NumberOfUnaryBits;i++) {

        std::cout << EncodedBits.test(i);
    }
    //*********************************************
    if (XorBits)
    {
        std::cout << " \n ********* This is the Encrypted Being Sent **************  Encrypt by  XOR ***************** \n\n\n";
        for (i = 0;i < NumberOfUnaryBits;i++)
        {
            if (EncryptBits.test(i) == 1) EncodedBits.flip(i);
            std::cout << EncodedBits.test(i);
        }
    }
      std::cout << " \n   ****************************************************************************************     END OF ENCODING             ********************** \n\n";
    
      //Decrypt
      if (XorBits)
      {
          std::cout << " \n ********* This is the Encrypted Being Sent **************  Encrypt by  XOR ***************** \n\n\n";
          for (i = 0;i < NumberOfUnaryBits;i++)
          {
              if (EncryptBits.test(i) == 1) EncodedBits.flip(i);
              std::cout << EncodedBits.test(i);
          }
      }
    //NumberOfUnaryBits = EncodedBits.size();
    TestBit = EncodedBits.test(0);
    TempTest = TestBit;
    ChunkCount = 0;
    kk = 0;
    V = 1;
    BitCount = 0;
    Vstart = TestBit;
    // First bit in message
    while (BitCount < NumberOfUnaryBits)
    {
        TestBit = EncodedBits.test(BitCount);
        if (TestBit != Vstart)
        {
            // a change

            // vr,vr,vr....chunks size is the begin ov the V to the begin of r

            if (V == 1) {
                VArray[ChunkCount] = kk;// for "A" there would be 66 ones (Array index from 0 to 65)

                V = 0;// WE HAVE GOTTEN A V
                R = 1;
                SizeChunk[ChunkCount] = kk;
                kk = 0;
                Vstart = TestBit;
            }
            else
            {
                RArray[ChunkCount] = kk;// -VArray[ChunkCount];

                ChunkCount++;
                R = 0;// We have gotten an R
                // so the first zero (assuming v's were ones)
                V = 1;
                ii = kk;
                kk = 0;

                Vstart = TestBit;
            }
            !Vstart;




        };
        kk++;
        BitCount++;
    };

    // finsihed and never found and R or V fill in remainder with kk-1;
    //****************************************************************************************
    std::cout << " \n       This was the original message    \n ";
    BytesFromInputLoop= 0;
    while (BytesFromInputLoop < NumberBytes)
    {

        xin = InputBytes[BytesFromInputLoop];// 8 bits read in  
        std::cout << " xin = " << xin << " ";;
        for (i = 0;i < 8;i++)
        {
            TestBit = bool(Mask[i] & xin);
            PlainTextBiits.set(BitCount, TestBit);
            std::cout << TestBit;
            BitCount++;
        }
        BytesFromInputLoop++;

    }
    BitCount = 0;
    if (R == 1) RArray[ChunkCount] = kk;

    std::cout << "\n                      This is the reconstructed RV Arrays from the encoded stream \n";
    for (i = 0;i <= ChunkCount;i++) {

        std::cout << i << "  V" << i << "= " << VArray[i] << "     ";

        std::cout << " R" << i << "= " << RArray[i];

        std::cout << "\n";

    };

  // **************************************** Now Retrieve ascii message **************

    

    std::cout << "\n                   Run throug the chunks and re-assemble the original bitstream \n";
    std::cout << " \n             First Step is to dscramble text bt un swapping the chunks .. if it was does done     ";
    CharTemp = 0;
    Kbytes = 0;


    //*********************************** Unswap **************************
   
    // Clear arrays
    for (i = 0;i < 200;i++) 
    {
        OriginalVArray[i] = 0;
        OriginalRArray[i] = 0;
    }
   
        // the first one receuved is VArray[0] which is then placed in NUMS[i], if Nums[0]=3. then it is placed in the third one in or i=2
        for (i = 0;i <= ChunkCount;i++) {
            ii=nums[i];
            OriginalVArray[ii] = VArray[i];
            OriginalRArray[ii] = RArray[i];
        }
        std::cout << "\n **********     Descrambled Array *****************  \n";
        for (i = 0;i <= ChunkCount;i++) {

            std::cout << " V" << i << "= " << OriginalVArray[i] << "     ";

            std::cout << " R" << i << "= " << OriginalRArray[i];

            std::cout << "\n";

        };
          
  
   
    std::cout << "        Decoded  bit stream ********************  \n";
    for (i = 0;i <= 200;i++) SizeChunk[i] = 0;
    BitCount = 0;// place bits from 0 to7 for bytes etc.
    DecodedBits.reset();
        // run through Varrays and assemple bytes
    //                                                       012     345    678         9
    //"AB " 01000001 01000010 break into chunks size =3  ,   010     000    010         100         001         0 
    //***************                                      R=2,V=3 V=1,R=4   R=2,V=3    R=1,V=1    R=3.V=2   R=2.V=1
    // Calculate size of chunks 
    for (i = 0;i <= ChunkCount;i++)
    {
        SizeChunk[i] = 0;
        rtemp = OriginalRArray[i] - 1;
        vtemp = OriginalVArray[i] - 1;

        // begin at BitCount to place next
        // find top bit of vtemp
        DecodeMask = 128; //0b10000000
        if (vtemp == 0)// there are only zeroes
        {
            SizeChunk[i] = rtemp;
        }
        else
        {
            for (ii = 0;ii < 8;ii++)
            {
                temp = (DecodeMask & vtemp);// find  the first one
                TestBit = bool(temp);
                if (TestBit)
                {
                    SizeChunk[i] = 8 - ii + rtemp;
                    break;
                }
                DecodeMask >>= 1;
            };
        };
       
        CharTemp = vtemp;
        TempTest = 0;
        std::cout << " V" << i << " =" << OriginalVArray[i] << "  R" << i << " =" << OriginalRArray[i] << "  Size = " << SizeChunk[i] << "  \n";
    };
    std::cout << "  Now decode the RV arrays into bytes   \n";
    CharTemp = 0x00;
    for (i = 0;i <= ChunkCount;i++)
    {
        TempTest = 0;
        rtemp = OriginalRArray[i] - 1;
        vtemp = OriginalVArray[i] - 1;
        j = SizeChunk[i];
        DecodeMask = 0x01;
        DecodeMask <<= (j - 1);
        // first we add the leading zeros
        for (kk = 0;kk < rtemp;kk++)
        {
            DecodedBits.reset(BitCount);
            BitCount++; // next bit position to test
            DecodeMask >>= 1;
        }
        TempTest = 0;
        if (vtemp > 0)
        {
            // run through Varrays and assemple bytes
//                                                       012     345    678         9
//"AB " 01000001 01000010 break into chunks size =3  ,   010     000    010         100         001         0 
//***************                                      R=2,V=3 V=1,R=4   R=2,V=3    R=1,V=1    R=3.V=2   R=2.V=1
            for (ii = 0;ii < j;ii++)
            {
                if (DecodeMask < 1) break;
                temp = DecodeMask & vtemp;// find  the first one
                 DecodeMask >>= 1;
                TestBit = bool(temp);
                if (TempTest)// found the first one
                {

                    TempTest = 1;
                    // now run throught bits and add them
                  
                    if (TestBit) DecodedBits.set(BitCount, TestBit);
                    BitCount++;

                }
                else
                {
                    if (TestBit) TempTest = 1;
                    DecodedBits.set(BitCount, TestBit);// start of V
                    BitCount++;
                }
                
                
            };
        }
       // BitCount++;
    };
        


  
 
    std::cout << "  Message was \n";

    kk = 0;ii = 0;
       while(ii<BitCount)
       {
           CharTemp = 0;
           kk = 0x80;
           // the first bit is the MSB 0x80 or 128;
           for (i = 0;i < 8;i++)
           {
               TestBit = DecodedBits.test(ii);
               if (TestBit)CharTemp = CharTemp + kk;
               kk >>= 1;
                  
               ii++;
           }
           std::cout << CharTemp;
           
        };
  
       std::cout << " \n ************* MESSAGE COMPLETE *****************\n ";
}
       
  
















