if vp < 20 and vp >0:                                ## vp : 체결강도
    vp = 20

elif vp <= 450 and vp > 180:
    vp = 180


vari = (vp+20)/40


if real < 0 :
    day_score = (-1/(22-2*vari))*(real+1-vari)**2 + 1-0.5*vari

elif 0 <= real and real < 4:
    day_score = (-1/(9+vari))*(real-3)**2 + 1 +abs(-5 + 1.5*vari)
    
else:
    day_score = (-1/(16-vari))*(real-3)**2 + 1 +abs(-5 + 1.5*vari)
    
    
    
if vp >450 or vp < 15:
    day_score = -10                                 ## day_score  : 점수
    

if real >= 0 and  data.iloc[i]['등락율'] < 0:                         ## real : 당일 실등락율 (종가 - 시가)

    day_score = day_score *0.5
    
# if real < 0 and  data.iloc[i]['등락율'] > 0:
#     day_score = day_score *0.5

if High != Low :                                                                                 
    day_score = day_score * 0.5 * 1.5**abs((Close - Open) / (High - Low))
else:
    day_score = day_score * 0.5