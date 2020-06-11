import mysql.connector
from mysql.connector import Error

def moistureM(argument): 
    i = argument
    y=0
    if(i < 450): 
        return 0;
    elif (450 < i < 590):
            y = (i-450)/(590-450)
            return y;
    elif (590< i <730):
        y = (730 - i)/(730 - 590)
        return y;
    elif (i > 730):
        return 0;
    
def moistureL(argument): 
    i = argument
    y=0
    if(i < 450): 
        return 1;
    elif (450< i <590):
        y = (450 - i)/(590 - 450)
        return y;
    elif (i > 590):
        return 0;
    
def moistureH(argument): 
    i = argument
    y=0
    if(i < 590): 
        return 0;
    elif (590 < i < 730):
            y = (i - 590)/(730 - 590)
            return y;
    elif (i > 730):
        return 1;
    


def temperatureM(argument):
    i = argument
    y=0
    if(i < 20): 
        return 0;
    elif (20 < i < 25):
            y = (i-20)/(25-20)
            return y;
    elif (25< i <30):
        y = (30 - i)/(30 - 25)
        return y;
    elif (30< i <40):
        y = (40 - i)/(40 - 30)
        return y;
    elif (i > 40):
        return 0;
    
def temperatureL(argument):
    i = argument
    y=0
    if(i < 20): 
        return 1;
    elif (20 < i < 25):
            y = (25-i)/(25-20)
            return y;
    elif (i > 25):
        return 0;
    
def temperatureH(argument):
    i = argument
    y=0
    if(i < 30): 
        return 0;
    elif (30 < i < 40):
            y = (i-30)/(40-30)
            return y;
    elif (i > 40):
        return 1;

def humidityM(argument):
    i = argument
    y=0
    if(i < 30): 
        return 0;
    elif (30 < i < 50):
            y = (i-30)/(50-30)
            return y;
    elif (50< i <70):
        y = (70 - i)/(70 - 50)
        return y;
    elif (i > 70):
        return 0;
    
def humidityL(argument):
    i = argument
    y=0
    if(i < 30): 
        return 1;
    elif (30 < i < 50):
            y = (50-i)/(50-30)
            return y;
    elif (i > 50):
        return 0;
    
def humidityH(argument):
    i = argument
    y=0
    if(i < 50): 
        return 0;
    elif (50 < i < 70):
            y = (i-50)/(70-50)
            return y;
    elif (i > 70):
        return 1;
    

def rainM(argument):
    i = argument
    y=0
    if(i < 2.5): 
        return 0;
    elif (2.5 < i < 5.5):
            y = (i-2.5)/(5.5-2.5)
            return y;
    elif (5.5< i <7.5):
        y = (7.5 - i)/(7.5 - 5.5)
        return y;
    elif (i > 7.5):
        return 0;
    
def rainL(argument):
    i = argument
    y=0
    if(i < 2.5): 
        return 1;
    elif (2.5 < i < 5.5):
            y = (5.5-i)/(5.5-2.5)
            return y;
    elif (i > 5.5):
        return 0;
    
def rainH(argument):
    i = argument
    y=0
    if(i < 5.5): 
        return 0;
    elif (5.5 < i < 7.5):
            y = (i-5.5)/(7.5-5.5)
            return y;
    elif (i > 7.5):
        return 1;   


def ageL(argument):
    i = argument
    y=0
    if(i < 0): 
        return 0;
    elif (0 < i < 10):
            y = (10-i)/(10-0)
            return y;
    elif (10 < i < 20):
        y = (20 -i)/(20 - 10)
        return y;
    else:
        return 0;

def ageM(argument):
    i = argument
    y=0
    if(i < 20): 
            y = (20-i)/(20-10)
            return y;
    elif (20 < i < 30):
            y = (30-i)/(30-20)
            return y;
    elif (30 < i < 40):
        y = (40 - i)/(40 - 30)
        return y;
    else :
        return 0;
def ageH(argument):
   i = argument
   y=0
   if(i < 40): 
        return 0;
   elif (40 < i < 50):
            y = (50-i)/(50-40)
            return y;
   elif (50 < i < 60):
        y = (60 - i)/(60 - 50)
        return y;
   else :
        return 0;
    
    
def colourM(argument):
    i = argument
    y=0
    if(i < 50): 
        return 0;
    elif (50 < i < 175):
            y = (i-50)/(175-50)
            return y;
    elif (175 < i < 300):
        y = (300 - i)/(300 - 175)
        return y;
    elif (i > 300):
        return 0;
    
def colourL(argument):
    i = argument
    y=0
    if(i < 30): 
        return 1;
    elif (30 < i < 175):
            y = (175-i)/(175 - 30)
            return y;
    elif (i > 175):
        return 0;
    
def colourH(argument):
    i = argument
    y=0
    if(i < 175): 
        return 0;
    elif (175 < i < 300):
            y = (i-175)/(300-175)
            return y;
    elif (i > 300):
        return 1; 
    
def getDist(list1, list2):              #manhatan distance
    sum = 0
    n = len(list1)
    for i in range(n):
          sum = sum + abs(list1[i] - list2[i]) 
    return sum;
    
def getRequest():
    try:
        connection = mysql.connector.connect(host='localhost',
                                             database='smart_irrigation_1',
                                             user='sumit',
                                             password='senti143')
        if connection.is_connected():
            db_Info = connection.get_server_info()
            print("Connected to MySQL Server version ", db_Info)
            #cursor = connection.cursor()
            #global conneection timeout arguments
            #cursor.execute("select * from data;")
            #record = cursor.fetchall()
            #print("You're connected to database: ", record)
            cursor1 = connection.cursor()
            cursor1.execute("select avg(ph_value),avg(rain),avg(moisture),avg(greenness),avg(red),avg(blue),avg(ir),avg(ldr) from data;")
            record1 = cursor1.fetchall()
            #print("Avg ", record1)
            cursor2 = connection.cursor()
            cursor2.execute("SELECT temperature,humidity,pressure FROM data2 ORDER BY id DESC LIMIT 1;")
            record2 = cursor2.fetchall()
            #print("new table",record2)
            record=[None]*11
            for row in record1:
                for i in range(8):
                    record[i] = row[i]
            for row in record2:
                for i in range(3):
                    record[i+8] = row[i]
            #print(record)
                
    except Error as e:
        print("Error while connecting to MySQL", e)
    finally:
        if (connection.is_connected()):
            #cursor.close()
            cursor1.close()
            cursor2.close()
            connection.close()
            print("MySQL connection is closed")
    return record;
    

def postData(data1):
    try:
        connection = mysql.connector.connect(host='localhost',
                                             database='smart_irrigation_1',
                                             user='sumit',
                                             password='senti143')
        if connection.is_connected():
            db_Info = connection.get_server_info()
            print("Connected to MySQL Server version ", db_Info)
            cursor1 = connection.cursor()
            data = data1
            inst = " INSERT INTO data3 (waterhrs) VALUES (%s) ;"
            cursor1.execute(inst,(data,))
            print(cursor1.description)
    except Error as e:
        print("Error while connecting to MySQL", e)
    finally:
        if (connection.is_connected()):
            #cursor.close()
            cursor1.close()
            connection.close()
            print("MySQL connection is closed")
        
    return ;
    
def write(parm1):
    f = open("E:\\xampp\\htdocs\\smart1\\fireye.txt","w+")
    f.write(parm1)
    f.close
    
    return ;

# Driver program 
if __name__ == "__main__": 
    listL = [1, 0, 0]
    listM = [0, 1, 0]
    listH = [0, 0, 1]
    waterAmt = [0, 1, 2, 3]
    operation = []
    
    record = []
    record = getRequest()
#........................moisture..................................    
    v = record[2]
    listN = [moistureL(v), moistureM(v), moistureH(v)]
    dist = [-1, -1, -1]
    dist[0] = getDist(listL, listN)
    dist[1] = getDist(listM, listN)
    dist[2] = getDist(listH, listN)
    minarg = dist.index(min(dist))
    if minarg == 0 :
        operation.append(waterAmt[1])
    elif minarg == 1 :
        operation.append(waterAmt[2])
    elif minarg == 2 :
        operation.append(waterAmt[3])
#........................temperature.............................
    v = record[8]
    listN = [temperatureL(v), temperatureM(v), temperatureH(v)]
    dist = [-1, -1, -1]
    dist[0] = getDist(listL, listN)
    dist[1] = getDist(listM, listN)
    dist[2] = getDist(listH, listN)
    minarg = dist.index(min(dist))
    if minarg == 0 :
        operation.append(waterAmt[1])
    elif minarg == 1 :
        operation.append(waterAmt[2])
    elif minarg == 2 :
        operation.append(waterAmt[3])
        
#......................Humidity..............................
    v = record[9]
    listN = [humidityL(v), humidityM(v), humidityH(v)]
    dist = [-1, -1, -1]
    dist[0] = getDist(listL, listN)
    dist[1] = getDist(listM, listN)
    dist[2] = getDist(listH, listN)
    minarg = dist.index(min(dist))
    if minarg == 0 :
        operation.append(waterAmt[1])
    elif minarg == 1 :
        operation.append(waterAmt[2])
    elif minarg == 2 :
        operation.append(waterAmt[3])
#.....................Rain...................................
    v = record[1]
    listN = [rainL(v), rainM(v), rainH(v)]
    dist = [-1, -1, -1]
    dist[0] = getDist(listL, listN)
    dist[1] = getDist(listM, listN)
    dist[2] = getDist(listH, listN)
    minarg = dist.index(min(dist))
    if minarg == 0 :
        operation.append(waterAmt[1])
    elif minarg == 1 :
        operation.append(waterAmt[2])
    elif minarg == 2 :
        operation.append(waterAmt[3])
#...................age......................................
    v = 35
    listN = [ageL(v), ageM(v), ageH(v)]
    dist = [-1, -1, -1]
    dist[0] = getDist(listL, listN)
    dist[1] = getDist(listM, listN)
    dist[2] = getDist(listH, listN)
    minarg = dist.index(min(dist))
    if minarg == 0 :
        operation.append(waterAmt[1])
    elif minarg == 1 :
        operation.append(waterAmt[2])
    elif minarg == 2 :
        operation.append(waterAmt[3])
#...................colour....................................
    v = record[3]
    listN = [colourL(v), colourM(v), colourH(v)]
    dist = [-1, -1, -1]
    dist[0] = getDist(listL, listN)
    dist[1] = getDist(listM, listN)
    dist[2] = getDist(listH, listN)
    minarg = dist.index(min(dist))
    if minarg == 0 :
        operation.append(waterAmt[1])
    elif minarg == 1 :
        operation.append(waterAmt[2])
    elif minarg == 2 :
        operation.append(waterAmt[3])
        
    print(operation)
    if sum(operation) == 0:
        print("No Water Supply")
        #postData(str(0))
        write(str(0))
    else:
        print("Water Supply Hours: ", min(operation))
        #postData(str(min(operation)))
        write(str(min(operation)))
    