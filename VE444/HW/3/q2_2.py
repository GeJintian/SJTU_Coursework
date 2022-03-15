
class Favor():
    def __init__(self):
        self.movie_favor = {}
        f = open("Employee_Movie_Choices.txt","r")
        line = f.readline()
        while line:
            line = f.readline()
            line = line[:-1]
            x = line.split()
            if len(x) == 0: break
            string = ''.join(x[1:])
            if (x[0] not in self.movie_favor):
                self.movie_favor[x[0]] = [string]
            else:
                self.movie_favor[x[0]].append(string)
        f.close()
        #print(self.movie_favor)

    def heuristic(self, movie_list):
        people_list = set([])
        for people in self.movie_favor:
            for movie in movie_list:
                if movie in self.movie_favor[people]:
                    people_list.add(people)
        return len(people_list)


favor = Favor()
movie_set = []
f = open("Employee_Movie_Choices.txt","r")
line = f.readline()
while line:
    line = f.readline()
    line = line[:-1]
    x = line.split()
    if len(x) == 0: break
    string = ''.join(x[1:])
    if string not in movie_set: movie_set.append(string)
f.close()
movie_number = len(movie_set)
score = [0]*movie_number
rec_mv = []
for i in range(movie_number):
    for j in range(movie_number):
        rec_mv.append(movie_set[j])
        score[j] = favor.heuristic(rec_mv)
        del rec_mv[-1]
    idx = score.index(max(score))
    rec_mv.append(movie_set[idx])
    if score[idx] == 8:
        break
for k in rec_mv:
    print(k,"\t")
