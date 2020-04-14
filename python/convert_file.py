#GCP_coord = open('LPS_GCP.txt', 'w')
Metashape_data = open('GCPs.txt', 'r')
equivalence_relat = open('../saida/1Faixa/GCP_ImagePoints.txt', 'r')

Metashape_list = []
LPS_list = []
lps_aux = []
aux_lis = []

l = 0
l2 = 0

if equivalence_relat:
    print("SUCESS!")

    for line in equivalence_relat:
        if l == 0:
            l += 1
            continue
        else:
            aux_lis.append(line.split("\t"))
    

if Metashape_data:
    print("SUCESS!")

    for line in Metashape_data:
        if l2 < 2:
            l2 += 1
            continue
        else:
            Metashape_list.append(line.split("\t"))

for i in aux_lis:
    lps_aux.append(i[0])

    for j in Metashape_list:
        if (j[0] + '\n') == i[1]:
            lps_aux.append(j[1])
            lps_aux.append(j[2])
            lps_aux.append(j[3])
        
    LPS_list.append(lps_aux)
    lps_aux = []

GCP_coord = open('LPS_GCP.txt', 'w')

for i in range(len(LPS_list)):
    if i == len(LPS_list) -1:
        GCP_coord.write(LPS_list[i][0] + '\t' + LPS_list[i][1] + '\t' + LPS_list[i][2] + '\t' + LPS_list[i][3])
    else:
        GCP_coord.write(LPS_list[i][0] + '\t' + LPS_list[i][1] + '\t' + LPS_list[i][2] + '\t' + LPS_list[i][3] + '\n')

GCP_coord.close()
equivalence_relat.close()
Metashape_data.close()
