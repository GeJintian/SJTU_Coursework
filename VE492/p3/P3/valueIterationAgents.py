import mdp, util

from learningAgents import ValueEstimationAgent
import collections

class ValueIterationAgent(ValueEstimationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A ValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100):
        """
          Your value iteration agent should take an mdp on
          construction, run the indicated number of iterations
          and then act according to the resulting policy.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state, action, nextState)
              mdp.isTerminal(state)
        """
        self.mdp = mdp
        self.discount = discount
        self.iterations = iterations
        self.values = util.Counter() # A Counter is a dict with default 0
        self.runValueIteration()

    def runValueIteration(self):
        # Write value iteration code here
        "*** YOUR CODE HERE ***"
        for ite in range(self.iterations):
            OldValue = self.values.copy()
            states = self.mdp.getStates()
            for state in states:
                actions = self.mdp.getPossibleActions(state)
                chosen_value = -10e9
                if len(actions)==0:
                    chosen_value = 0
                for action in actions:
                    Q_value = 0
                    pairs = self.mdp.getTransitionStatesAndProbs(state,action)
                    for pair in pairs:
                        next_state,prob = pair
                        reward = self.mdp.getReward(state,action,next_state)
                        Q_value += prob*(reward+self.discount*OldValue[next_state])
                    if Q_value > chosen_value:
                        chosen_value = Q_value
                self.values[state] = chosen_value


            


            
    def getValue(self, state):
        """
          Return the value of the state (computed in __init__).
        """
        return self.values[state]


    def computeQValueFromValues(self, state, action):
        """
          Compute the Q-value of action in state from the
          value function stored in self.values.
        """
        "*** YOUR CODE HERE ***"
        Q_value = 0
        pairs = self.mdp.getTransitionStatesAndProbs(state,action)
        for pair in pairs:
            next_state,prob = pair
            reward = self.mdp.getReward(state,action,next_state)
            Q_value += prob*(reward+self.discount*self.values[next_state])
        return Q_value


    def computeActionFromValues(self, state):
        """
          The policy is the best action in the given state
          according to the values currently stored in self.values.

          You may break ties any way you see fit.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return None.
        """
        "*** YOUR CODE HERE ***"
        actions = self.mdp.getPossibleActions(state)
        Q_value = -10e9
        if len(actions)==0:
            return None
        for action in actions:
            Q = self.computeQValueFromValues(state,action)
            if(Q_value < Q):
                chosen_action = action
                Q_value = Q
        return chosen_action


    def getPolicy(self, state):
        return self.computeActionFromValues(state)

    def getAction(self, state):
        "Returns the policy at the state (no exploration)."
        return self.computeActionFromValues(state)

    def getQValue(self, state, action):
        return self.computeQValueFromValues(state, action)

class AsynchronousValueIterationAgent(ValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        An AsynchronousValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs cyclic value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 1000):
        """
          Your cyclic value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy. Each iteration
          updates the value of only one state, which cycles through
          the states list. If the chosen state is terminal, nothing
          happens in that iteration.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state)
              mdp.isTerminal(state)
        """
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
        state_list = self.mdp.getStates()
        state_len = len(state_list)
        k = 0
        for i in range(self.iterations):
            if(k==state_len): k = 0
            actions = self.mdp.getPossibleActions(state_list[k])
            chosen_value = -10e9
            if len(actions)==0:
                chosen_value = 0
            for action in actions:
                Q_value = 0
                pairs = self.mdp.getTransitionStatesAndProbs(state_list[k],action)
                for pair in pairs:
                    next_state,prob = pair
                    reward = self.mdp.getReward(state_list[k],action,next_state)
                    Q_value += prob*(reward+self.discount*self.values[next_state])
                if Q_value > chosen_value:
                    chosen_value = Q_value
            self.values[state_list[k]] = chosen_value     
            k+=1     


class PrioritizedSweepingValueIterationAgent(AsynchronousValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A PrioritizedSweepingValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs prioritized sweeping value iteration
        for a given number of iterations using the supplied parameters.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100, theta = 1e-5):
        """
          Your prioritized sweeping value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy.
        """
        self.theta = theta
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
        states = self.mdp.getStates()

        #for predecessor
        prede = [set() for state in states]
        for state in states:
            actions = self.mdp.getPossibleActions(state)
            for action in actions:
                pairs = self.mdp.getTransitionStatesAndProbs(state,action)
                for pair in pairs:
                    next_state,_ = pair
                    prede[states.index(next_state)].add(state)

        #for queue
        Queue = util.PriorityQueue()
        for state in states:
            chosen_value = -10e9
            actions = self.mdp.getPossibleActions(state)
            if len(actions)==0:
                    chosen_value = 0
            for action in actions:
                Q_value = self.computeQValueFromValues(state,action)
                if Q_value > chosen_value:
                    chosen_value = Q_value
            diff = abs(self.values[state] - chosen_value)
            Queue.push(state, -diff)


        #for first queue
        for i in range(self.iterations):
            if Queue.isEmpty(): 
                return
            state = Queue.pop()
            #Update the value of s
            chosen_value = -10e9
            actions = self.mdp.getPossibleActions(state)
            if len(actions)==0:
                    chosen_value = 0
            for action in actions:
                Q_value = self.computeQValueFromValues(state,action)
                if Q_value > chosen_value:
                    chosen_value = Q_value
            self.values[state] = chosen_value

            #For each predecessor of s
            index = states.index(state)
            predecessors = prede[index]
            for p in predecessors:
                chosen_value = -10e9
                actions = self.mdp.getPossibleActions(p)
                if len(actions)==0:
                        chosen_value = 0
                for action in actions:
                    Q_value = self.computeQValueFromValues(p,action)
                    if Q_value > chosen_value:
                        chosen_value = Q_value
                diff = abs(self.values[p] - chosen_value)
                if diff > self.theta:
                    Queue.update(p,-diff)



            

            



        


