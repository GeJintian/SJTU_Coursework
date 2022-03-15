from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"
        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        x,y = newPos
        xghost,yghost = newGhostStates[0].getPosition()
        ghost_dis = abs(x-xghost) + abs(y-yghost)
        for ghost in newGhostStates:
            x_temp,y_temp = ghost.getPosition()
            new_ghost_dis = abs(x-x_temp) + abs(y-y_temp)
            if (new_ghost_dis < ghost_dis):
                ghost_dis = new_ghost_dis
        if min(newScaredTimes) > 2:
            inv_ghost_dis = 0
        elif ghost_dis < 2:
            inv_ghost_dis = 3/(0.01+ghost_dis)
        else:
            inv_ghost_dis = 2/(ghost_dis)
        food_list = newFood.asList()
        food_num = len(food_list)
        if food_num != 0:
            xfood, yfood = food_list[0]
            food_dis = abs(x-xfood)+abs(y-yfood)
            for food in food_list:
                x_temp, y_temp = food
                new_food_dis = abs(x-x_temp)+abs(y-y_temp)
                if (new_food_dis < food_dis):
                    food_dis = new_food_dis
            food_dis_inv = 1/(food_dis+0.1)
        else:
            food_dis_inv = 1
        value = -food_num +  food_dis_inv - inv_ghost_dis
        return value

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        Actions = gameState.getLegalActions()
        v = []
        for action in Actions:
            succ = gameState.generateSuccessor(0, action)
            v = v + [self.minValue(succ, 1)]
        max_value = max(v)
        index = v.index(max_value)
        return Actions[index]
    
    def termValue(self, gameState):
        return self.evaluationFunction(gameState)

    def minValue(self, gameState, count):
        "For ghosts to make a choice"
        ghostNum = gameState.getNumAgents() - 1
        v = self.minValue_helper(ghostNum, 1, gameState, count)
        return v


    def minValue_helper(self, ghostNum, ghostID, gameState, count):
        if gameState.isWin() or gameState.isLose():
            return self.termValue(gameState)
        Actions = gameState.getLegalActions(ghostID)
        v = 10e9
        for action in Actions:
            succ = gameState.generateSuccessor(ghostID, action)
            if(ghostID == ghostNum):
                if count == self.depth:
                    v = min(v, self.termValue(succ))
                else:
                    v = min(v, self.maxValue(succ, count + 1))
            else:
                v = min(v,self.minValue_helper(ghostNum, ghostID + 1, succ, count))
        
        return v

    def maxValue(self, gameState, count):
        if gameState.isWin() or gameState.isLose():
            return self.termValue(gameState)
        Actions = gameState.getLegalActions(0)
        v = -10e9
        for action in Actions:
            succ = gameState.generateSuccessor(0,action)
            v = max(v, self.minValue(succ, count))
        return v

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        a = -10e9
        b = 10e9
        Actions = gameState.getLegalActions()
        v = []
        v_max = -10e9
        for action in Actions:
            succ = gameState.generateSuccessor(0, action)
            actV = self.minValue(succ, 1,a,b)
            v_max = max(v_max,actV)
            v = v + [actV]
            a = max(a, v_max)
        index = v.index(v_max)
        return Actions[index]
    
    
    def termValue(self, gameState):
        return self.evaluationFunction(gameState)

    def minValue(self, gameState, count,a,b):
        "For ghosts to make a choice"
        ghostNum = gameState.getNumAgents() - 1
        v = self.minValue_helper(ghostNum, 1, gameState, count,a,b)
        return v


    def minValue_helper(self, ghostNum, ghostID, gameState, count,a,b):
        if gameState.isWin() or gameState.isLose():
            return self.termValue(gameState)
        Actions = gameState.getLegalActions(ghostID)
        v = 10e9
        for action in Actions:
            succ = gameState.generateSuccessor(ghostID, action)
            if(ghostID == ghostNum):
                if count == self.depth:
                    v = min(v, self.termValue(succ))
                else:
                    v = min(v, self.maxValue(succ, count + 1,a,b))
            else:
                v = min(v,self.minValue_helper(ghostNum, ghostID + 1, succ, count,a,b))
            if v < a: return v
            b = min(b,v)
        
        return v

    def maxValue(self, gameState, count,a,b):
        if gameState.isWin() or gameState.isLose():
            return self.termValue(gameState)
        Actions = gameState.getLegalActions(0)
        v = -10e9
        for action in Actions:
            succ = gameState.generateSuccessor(0,action)
            v = max(v, self.minValue(succ, count,a,b))
            if v > b: return v
            a = max(a,v)
        return v

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        Actions = gameState.getLegalActions()
        v = []
        for action in Actions:
            succ = gameState.generateSuccessor(0, action)
            v = v + [self.minValue(succ, 1)]
        max_value = max(v)
        index = v.index(max_value)
        return Actions[index]
    
    def termValue(self, gameState):
        return self.evaluationFunction(gameState)

    def minValue(self, gameState, count):
        "For ghosts to make a choice"
        ghostNum = gameState.getNumAgents() - 1
        v = self.minValue_helper(ghostNum, 1, gameState, count)
        return v


    def minValue_helper(self, ghostNum, ghostID, gameState, count):
        if gameState.isWin() or gameState.isLose():
            return self.termValue(gameState)
        Actions = gameState.getLegalActions(ghostID)
        prob = 1/len(Actions)
        v = 0
        for action in Actions:
            succ = gameState.generateSuccessor(ghostID, action)
            if(ghostID == ghostNum):
                if count == self.depth:
                    v = v + self.termValue(succ)*prob
                else:
                    v = v + self.maxValue(succ, count + 1)*prob
            else:
                v = v + self.minValue_helper(ghostNum, ghostID + 1, succ, count)*prob
        return v

    def maxValue(self, gameState, count):
        if gameState.isWin() or gameState.isLose():
            return self.termValue(gameState)
        Actions = gameState.getLegalActions(0)
        v = -10e9
        for action in Actions:
            succ = gameState.generateSuccessor(0,action)
            v = max(v, self.minValue(succ, count))
        return v

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    """
    evaluationFunction = util.lookup('scoreEvaluationFunction', globals())

    def termValue(gameState):
        return evaluationFunction(gameState)

    def minValue(gameState, count):
        if gameState.isWin() or gameState.isLose():
            return termValue(gameState)
        Actions = gameState.getLegalActions(1)
        prob = 1/len(Actions)
        v = 0
        for action in Actions:
            succ = gameState.generateSuccessor(1, action)
            if count == 2:
                v = v + termValue(succ)*prob
            else:
                v = v + maxValue(succ, count + 1)*prob
        return v

    def maxValue(gameState, count):
        if gameState.isWin() or gameState.isLose():
            return termValue(gameState)
        Actions = gameState.getLegalActions(0)
        v = -10e9
        for action in Actions:
            succ = gameState.generateSuccessor(0,action)
            v = max(v, minValue(succ,count))
        return v
    
    result = maxValue(currentGameState, 1)
    return result
    """
    newFood = currentGameState.getFood()
    newPos = currentGameState.getPacmanPosition()
    newGhostStates = currentGameState.getGhostStates()
    newCap = currentGameState.getCapsules()
    ghost_dis = 10e9
    for ghost in newGhostStates:
        if ghost.scaredTimer < 2:
            ghost_dis = min(ghost_dis, manhattanDistance(newPos,ghost.getPosition()))
        else:
            ghost_dis = 10
    if ghost_dis < 2:
        inv_ghost_dis = 10000/(0.01+ghost_dis)
    else:
        inv_ghost_dis = 1/(ghost_dis)
    food_list = newFood.asList()
    food_dis = 10e9
    food_num = len(food_list)
    for food in food_list:
        food_dis = min(food_dis, manhattanDistance(food,newPos))
    food_dis_inv = 1/(food_dis+0.1)
    cap_num = len(newCap)

    value = currentGameState.getScore()-500*food_num  +  50*food_dis_inv - inv_ghost_dis - 1000*cap_num

    return value

# Abbreviation
better = betterEvaluationFunction
