void __fastcall ServerManager__UpdateServerPosition(ServerManager_o *this, bool force)
{
  void *v2; // rdx
  int v3; // ecx
  int v4; // er8
  char v5; // r9
  ServerManager_o *v6; // r15
  _DWORD *v7; // r12
  _DWORD *v8; // r13
  _QWORD *v9; // r8
  int *v10; // rcx
  _QWORD *v11; // rbx
  int *v12; // rsi
  _QWORD *v13; // rbp
  int *v14; // r9
  _QWORD *v15; // r14
  float *v16; // rdx
  __m128 v17; // xmm1
  __m128 v18; // xmm0
  __m128 v19; // xmm2
  __m128 v20; // xmm3
  __m128 v21; // xmm2
  __m128 v22; // xmm1
  __m128 v23; // xmm2
  __m128 v24; // xmm2
  float v25; // xmm0_4
  float v26; // xmm0_4
  __m128 v27; // xmm1
  __m128 v28; // xmm0
  __m128 v29; // xmm2
  __m128 v30; // xmm3
  __m128 v31; // xmm2
  __m128 v32; // xmm1
  __m128 v33; // xmm2
  __m128 v34; // xmm2
  float v35; // xmm0_4
  float v36; // xmm0_4
  float v37; // xmm2_4
  float v38; // xmm3_4
  float v39; // xmm0_4
  float v40; // xmm4_4
  float v41; // xmm1_4
  __m128 v42; // xmm4
  float v43; // xmm0_4
  __m128 v44; // xmm4
  int v45; // ecx
  int v46; // ecx
  float *v47; // rbp
  System_Byte_array *v48; // rdi
  __int64 v49; // rax
  __int64 v50; // r14
  __int64 v51; // rdx
  int v52; // ecx
  int v53; // er8
  char v54; // r9
  float v55; // xmm2_4
  float v56; // xmm2_4
  unsigned __int64 v57; // rdi
  System_Array_o *v58; // rax
  void *v59; // rdx
  int v60; // ecx
  int v61; // er8
  char v62; // r9
  __int64 v63; // rax
  void *v64; // rdx
  int v65; // ecx
  int v66; // er8
  char v67; // r9
  __int64 v68; // rax
  void *v69; // rdx
  int v70; // ecx
  int v71; // er8
  char v72; // r9
  __int64 v73; // rax
  void *v74; // rdx
  int v75; // ecx
  int v76; // er8
  char v77; // r9
  __int64 v78; // rax
  void *v79; // rdx
  int v80; // ecx
  int v81; // er8
  char v82; // r9
  __int64 v83; // rax
  void *v84; // rdx
  int v85; // ecx
  int v86; // er8
  char v87; // r9
  __int64 v88; // rax
  void *v89; // rdx
  int v90; // ecx
  int v91; // er8
  char v92; // r9
  int16_t v93; // bp
  __int64 v94; // rax
  void *v95; // rdx
  int v96; // ecx
  int v97; // er8
  char v98; // r9
  __int64 v99; // rbx
  int16_t v100; // bp
  __int64 v101; // rax
  unsigned int v102; // ecx
  __int64 v103; // rax
  __m128 v104; // [rsp+0h] [rbp-A8h]
  int v105; // [rsp+0h] [rbp-A8h]
  int v106; // [rsp+0h] [rbp-A8h]
  int v107; // [rsp+0h] [rbp-A8h]
  int v108; // [rsp+0h] [rbp-A8h]
  int v109; // [rsp+0h] [rbp-A8h]
  int v110; // [rsp+0h] [rbp-A8h]
  int v111; // [rsp+0h] [rbp-A8h]
  __m128 v112; // [rsp+10h] [rbp-98h]
  __m128 v113; // [rsp+20h] [rbp-88h]
  __m128 v114; // [rsp+30h] [rbp-78h]
  float v115; // [rsp+60h] [rbp-48h]

  v6 = this;
  if ( !byte_1135A51 )
  {
    sub_322830(9314, force, v2, v3, v4, v5);
    byte_1135A51 = 1;
  }
  if ( !this->blocking_position_updates && this->loggedIn )
  {
    if ( force )
    {
      v7 = (_DWORD *)&this->time;
      v8 = (_DWORD *)&this->lastUpdate;
      v9 = (_QWORD *)&this->current_position.x;
      v10 = (int *)&this->current_position.z;
      v11 = (_QWORD *)&this->position.x;
      v12 = (int *)&this->position.z;
      v13 = (_QWORD *)&this->current_eulerAngles.x;
      v14 = (int *)&this->current_eulerAngles.z;
      v15 = (_QWORD *)&this->eulerAngles.x;
      v16 = &this->eulerAngles.z;
      goto LABEL_37;
    }
    v17 = (__m128)*(unsigned __int64 *)&this->current_position.x;
    v18 = (__m128)LODWORD(this->position.z);
    v19 = (__m128)LODWORD(this->current_position.z);
    v20 = (__m128)*(unsigned __int64 *)&this->position.x;
    if ( Class_UnityEngine_Vector3->_2.bitflags2 & 2 && !Class_UnityEngine_Vector3->_2.cctor_finished )
    {
      v114.m128_u64[1] = 0LL;
      il2cpp_runtime_class_init_0(
        (int)Class_UnityEngine_Vector3,
        force,
        (__int64)v2,
        v3,
        v4,
        v5,
        *(_QWORD *)&this->current_position.x,
        0,
        LODWORD(this->current_position.z),
        0LL,
        LODWORD(this->position.z),
        0,
        v20.m128_i8[0]);
      v20 = v114;
      v18 = v113;
      v19 = v112;
      v17 = v104;
    }
    if ( !byte_1137597 )
    {
      v104.m128_i32[2] = v17.m128_i32[2];
      v112 = v19;
      v113 = v18;
      v114.m128_i8[0] = v20.m128_i8[0];
      sub_322830(11911, force, v2, v3, v4, v5);
      byte_1137597 = 1;
    }
    v21 = _mm_unpacklo_ps(v19, v17);
    v22 = _mm_shuffle_ps(v17, v17, 229);
    v22.m128_f32[0] = v22.m128_f32[0] - COERCE_FLOAT(_mm_shuffle_ps(v20, v20, 229));
    v23 = _mm_sub_ps(v21, _mm_unpacklo_ps(v18, v20));
    if ( Class_System_Math->_2.bitflags2 & 2 && !Class_System_Math->_2.cctor_finished )
    {
      il2cpp_runtime_class_init_0(
        (int)Class_System_Math,
        force,
        (__int64)v2,
        v3,
        v4,
        v5,
        v22.m128_i32[0],
        v22.m128_i32[2],
        v23.m128_i32[0],
        (void *)v23.m128_u64[1],
        v113.m128_i32[0],
        v113.m128_i32[2],
        v114.m128_i8[0]);
      v23 = v112;
      v22.m128_i32[0] = v104.m128_i32[0];
    }
    v24 = _mm_mul_ps(v23, v23);
    v25 = (float)(COERCE_FLOAT(_mm_shuffle_ps(v24, v24, 229)) + (float)(v22.m128_f32[0] * v22.m128_f32[0]))
        + v24.m128_f32[0];
    if ( v25 < 0.0 )
      v26 = sqrtf(v25);
    else
      v26 = fsqrt(v25);
    v104.m128_f32[0] = v26;
    v27 = (__m128)*(unsigned __int64 *)&this->current_eulerAngles.x;
    v28 = (__m128)LODWORD(this->eulerAngles.z);
    v29 = (__m128)LODWORD(this->current_eulerAngles.z);
    v30 = (__m128)*(unsigned __int64 *)&this->eulerAngles.x;
    if ( Class_UnityEngine_Vector3->_2.bitflags2 & 2 && !Class_UnityEngine_Vector3->_2.cctor_finished )
    {
      v114.m128_u64[1] = 0LL;
      il2cpp_runtime_class_init_0(
        (int)Class_UnityEngine_Vector3,
        force,
        (__int64)v2,
        v3,
        v4,
        v5,
        v104.m128_i32[0],
        v104.m128_i32[2],
        *(_QWORD *)&this->current_eulerAngles.x,
        0LL,
        LODWORD(this->current_eulerAngles.z),
        0,
        v28.m128_i8[0]);
      v28 = v114;
      v29 = v113;
      v27 = v112;
    }
    if ( !byte_1137597 )
    {
      v112 = v27;
      v113 = v29;
      v114.m128_i8[0] = v28.m128_i8[0];
      sub_322830(11911, force, v2, v3, v4, v5);
      byte_1137597 = 1;
    }
    v31 = _mm_unpacklo_ps(v29, v27);
    v32 = _mm_shuffle_ps(v27, v27, 229);
    v32.m128_f32[0] = v32.m128_f32[0] - COERCE_FLOAT(_mm_shuffle_ps(v30, v30, 229));
    v33 = _mm_sub_ps(v31, _mm_unpacklo_ps(v28, v30));
    if ( Class_System_Math->_2.bitflags2 & 2 && !Class_System_Math->_2.cctor_finished )
    {
      il2cpp_runtime_class_init_0(
        (int)Class_System_Math,
        force,
        (__int64)v2,
        v3,
        v4,
        v5,
        v104.m128_i32[0],
        v104.m128_i32[2],
        v32.m128_i32[0],
        (void *)v32.m128_u64[1],
        v33.m128_i32[0],
        v33.m128_i32[2],
        v114.m128_i8[0]);
      v33 = v113;
      v32.m128_i32[0] = v112.m128_i32[0];
    }
    v34 = _mm_mul_ps(v33, v33);
    v35 = (float)(COERCE_FLOAT(_mm_shuffle_ps(v34, v34, 229)) + (float)(v32.m128_f32[0] * v32.m128_f32[0]))
        + v34.m128_f32[0];
    if ( v35 < 0.0 )
      v36 = sqrtf(v35);
    else
      v36 = fsqrt(v35);
    v9 = (_QWORD *)&this->current_position.x;
    v10 = (int *)&this->current_position.z;
    v11 = (_QWORD *)&this->position.x;
    v12 = (int *)&this->position.z;
    v13 = (_QWORD *)&this->current_eulerAngles.x;
    v14 = (int *)&this->current_eulerAngles.z;
    v15 = (_QWORD *)&this->eulerAngles.x;
    v16 = &this->eulerAngles.z;
    v7 = (_DWORD *)&this->time;
    v8 = (_DWORD *)&this->lastUpdate;
    v37 = this->time;
    v38 = this->lastUpdate;
    if ( v104.m128_f32[0] <= 0.001 && v36 <= 0.1 )
    {
      if ( (float)(v38 + 5.0) > v37 )
        return;
LABEL_37:
      *v8 = *v7;
      v45 = *v10;
      *v11 = *v9;
      *v12 = v45;
      v46 = *v14;
      *v15 = *v13;
      v47 = v16;
      *(_DWORD *)v16 = v46;
      v48 = Class_byte__;
      v49 = il2cpp_array_new_specific_0(Class_byte__, 46LL);
      v50 = v49;
      if ( v49 )
      {
        if ( !*(_DWORD *)(v49 + 24) )
          goto LABEL_87;
        *(_BYTE *)(v49 + 32) = 80;
        System_Buffer__BlockCopy((System_Array_o *)v6->usersecret, 0, (System_Array_o *)v49, 1, 8);
        v55 = v6->time;
        if ( Class_System_BitConverter->_2.bitflags2 & 2 && !Class_System_BitConverter->_2.cctor_finished )
        {
          il2cpp_runtime_class_init_0(
            (int)Class_System_BitConverter,
            0,
            v51,
            v52,
            v53,
            v54,
            LODWORD(v6->time),
            v104.m128_i32[2],
            v112.m128_i32[0],
            (void *)v112.m128_u64[1],
            v113.m128_i32[0],
            v113.m128_i32[2],
            v114.m128_i8[0]);
          v55 = *(float *)&v105;
        }
        v56 = v55 * 10000.0;
        v57 = (unsigned int)(int)v56;
        if ( v56 >= 9.223372e18 )
          v57 = (unsigned int)(int)(float)(v56 - 9.223372e18) ^ 0x8000000000000000LL;
        v58 = (System_Array_o *)System_BitConverter__GetBytes_6071872(v57);
        System_Buffer__BlockCopy(v58, 0, (System_Array_o *)v50, 9, 8);
        *(float *)&v106 = 10000.0 * v6->position.x;
        if ( !byte_11367E5 )
        {
          sub_322830(2253, 0, v59, v60, v61, v62);
          byte_11367E5 = 1;
        }
        v48 = Class_byte__;
        v63 = il2cpp_array_new_specific_0(Class_byte__, 4LL);
        if ( v63 )
        {
          if ( !*(_DWORD *)(v63 + 24) )
            goto LABEL_87;
          *(_DWORD *)(v63 + 32) = (int)*(float *)&v106;
          System_Buffer__BlockCopy((System_Array_o *)v63, 0, (System_Array_o *)v50, 17, 4);
          v107 = SLODWORD(v6->position.y);
          if ( !byte_11367E5 )
          {
            sub_322830(2253, 0, v64, v65, v66, v67);
            byte_11367E5 = 1;
          }
          v48 = Class_byte__;
          v68 = il2cpp_array_new_specific_0(Class_byte__, 4LL);
          if ( v68 )
          {
            if ( !*(_DWORD *)(v68 + 24) )
              goto LABEL_87;
            *(_DWORD *)(v68 + 32) = (int)(float)(*(float *)&v107 * 10000.0);
            System_Buffer__BlockCopy((System_Array_o *)v68, 0, (System_Array_o *)v50, 21, 4);
            v108 = *v12;
            if ( !byte_11367E5 )
            {
              sub_322830(2253, 0, v69, v70, v71, v72);
              byte_11367E5 = 1;
            }
            v48 = Class_byte__;
            v73 = il2cpp_array_new_specific_0(Class_byte__, 4LL);
            if ( v73 )
            {
              if ( !*(_DWORD *)(v73 + 24) )
                goto LABEL_87;
              *(_DWORD *)(v73 + 32) = (int)(float)(*(float *)&v108 * 10000.0);
              System_Buffer__BlockCopy((System_Array_o *)v73, 0, (System_Array_o *)v50, 25, 4);
              v109 = SLODWORD(v6->eulerAngles.x);
              if ( !byte_11367E5 )
              {
                sub_322830(2253, 0, v74, v75, v76, v77);
                byte_11367E5 = 1;
              }
              v48 = Class_byte__;
              v78 = il2cpp_array_new_specific_0(Class_byte__, 4LL);
              if ( v78 )
              {
                if ( !*(_DWORD *)(v78 + 24) )
                  goto LABEL_87;
                *(_DWORD *)(v78 + 32) = (int)(float)(*(float *)&v109 * 10000.0);
                System_Buffer__BlockCopy((System_Array_o *)v78, 0, (System_Array_o *)v50, 29, 4);
                v110 = SLODWORD(v6->eulerAngles.y);
                if ( !byte_11367E5 )
                {
                  sub_322830(2253, 0, v79, v80, v81, v82);
                  byte_11367E5 = 1;
                }
                v48 = Class_byte__;
                v83 = il2cpp_array_new_specific_0(Class_byte__, 4LL);
                if ( v83 )
                {
                  if ( !*(_DWORD *)(v83 + 24) )
                    goto LABEL_87;
                  *(_DWORD *)(v83 + 32) = (int)(float)(*(float *)&v110 * 10000.0);
                  System_Buffer__BlockCopy((System_Array_o *)v83, 0, (System_Array_o *)v50, 33, 4);
                  v111 = *(int *)v47;
                  if ( !byte_11367E5 )
                  {
                    sub_322830(2253, 0, v84, v85, v86, v87);
                    byte_11367E5 = 1;
                  }
                  v48 = Class_byte__;
                  v88 = il2cpp_array_new_specific_0(Class_byte__, 4LL);
                  if ( v88 )
                  {
                    if ( !*(_DWORD *)(v88 + 24) )
                      goto LABEL_87;
                    *(_DWORD *)(v88 + 32) = (int)(float)(*(float *)&v111 * 10000.0);
                    System_Buffer__BlockCopy((System_Array_o *)v88, 0, (System_Array_o *)v50, 37, 4);
                    if ( *(_DWORD *)(v50 + 24) <= 0x29u )
                      goto LABEL_87;
                    *(_BYTE *)(v50 + 73) = v6->trigger;
                    v93 = v6->groundedblend;
                    if ( !byte_11367E4 )
                    {
                      sub_322830(2250, 0, v89, v90, v91, v92);
                      byte_11367E4 = 1;
                    }
                    v48 = Class_byte__;
                    v94 = il2cpp_array_new_specific_0(Class_byte__, 2LL);
                    v99 = v94;
                    if ( v94 )
                    {
                      if ( !*(_DWORD *)(v94 + 24) )
                        goto LABEL_87;
                      *(_WORD *)(v94 + 32) = v93;
                      v100 = v6->notgroundedblend;
                      if ( !byte_11367E4 )
                      {
                        sub_322830(2250, 2, v95, v96, v97, v98);
                        byte_11367E4 = 1;
                      }
                      v48 = Class_byte__;
                      v101 = il2cpp_array_new_specific_0(Class_byte__, 2LL);
                      if ( v101 )
                      {
                        if ( *(_DWORD *)(v101 + 24) )
                        {
                          *(_WORD *)(v101 + 32) = v100;
                          if ( *(_DWORD *)(v99 + 24) )
                          {
                            v102 = *(_DWORD *)(v50 + 24);
                            if ( v102 > 0x2A )
                            {
                              *(_BYTE *)(v50 + 74) = *(_BYTE *)(v99 + 32);
                              if ( *(_DWORD *)(v99 + 24) > 1u && v102 > 0x2B )
                              {
                                *(_BYTE *)(v50 + 75) = *(_BYTE *)(v99 + 33);
                                if ( *(_DWORD *)(v101 + 24) )
                                {
                                  if ( v102 > 0x2C )
                                  {
                                    *(_BYTE *)(v50 + 76) = *(_BYTE *)(v101 + 32);
                                    if ( *(_DWORD *)(v101 + 24) > 1u && v102 > 0x2D )
                                    {
                                      *(_BYTE *)(v50 + 77) = *(_BYTE *)(v101 + 33);
                                      v6->trigger = 0;
                                      ServerManager__sendData(v6, (System_Byte_array *)v50);
                                      return;
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
LABEL_87:
                        v103 = sub_3231D0();
                        sub_322D10(v103, 0LL);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      sub_3230B0(v48);
    }
    v39 = this->heartbeat_roundtrip;
    v40 = this->rate_limit;
    v41 = this->noPlayerMultiplier;
    if ( Class_UnityEngine_Mathf->_2.bitflags2 & 2 && !Class_UnityEngine_Mathf->_2.cctor_finished )
    {
      v115 = this->rate_limit;
      il2cpp_runtime_class_init_0(
        (int)Class_UnityEngine_Mathf,
        (_BYTE)this - 52,
        (__int64)v16,
        (_DWORD)this + 484,
        (int)v9,
        (_BYTE)this - 16,
        (_DWORD)this + 472,
        v104.m128_i32[2],
        (_DWORD)this + 460,
        (void *)v112.m128_u64[1],
        (_DWORD)this + 476,
        v113.m128_i32[2],
        (_BYTE)this - 28);
      v40 = v115;
      v14 = (int *)&this->current_eulerAngles.z;
      v10 = (int *)v114.m128_u64[0];
      v9 = (_QWORD *)v113.m128_u64[0];
      v12 = (int *)v112.m128_u64[0];
      v16 = (float *)v104.m128_u64[0];
    }
    v42.m128_f32[0] = v40 + (float)(v39 * v41);
    v43 = fminf(1.0, v42.m128_f32[0]);
    v44 = _mm_cmpge_ss(v42, (__m128)0x3D4CCCCDu);
    if ( (float)(v38
               + COERCE_FLOAT(*(unsigned __int128 *)&_mm_andnot_ps(v44, (__m128)0x3D4CCCCDu) | LODWORD(v43) & v44.m128_i32[0])) <= v37 )
      goto LABEL_37;
  }
}
