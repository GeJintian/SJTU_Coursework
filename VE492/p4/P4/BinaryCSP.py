# Hint: from collections import deque
from Interface import *


# = = = = = = = QUESTION 1  = = = = = = = #


def consistent(assignment, csp, var, value):
    """
    Checks if a value assigned to a variable is consistent with all binary constraints in a problem.
    Do not assign value to var.
    Only check if this value would be consistent or not.
    If the other variable for a constraint is not assigned,
    then the new value is consistent with the constraint.

    Args:
        assignment (Assignment): the partial assignment
        csp (ConstraintSatisfactionProblem): the problem definition
        var (string): the variable that would be assigned
        value (value): the value that would be assigned to the variable
    Returns:
        boolean
        True if the value would be consistent with all currently assigned values, False otherwise
    """
    # TODO: Question 1
    constraints = csp.binaryConstraints
    for constraint in constraints:
        if(constraint.affects(var)):
            other = constraint.otherVariable(var)
            if assignment.isAssigned(other):
                if constraint.isSatisfied(value, assignment.assignedValues[other]) is not True:
                    return False
    return True


def recursiveBacktracking(assignment, csp, orderValuesMethod, selectVariableMethod, inferenceMethod):
    """
    Recursive backtracking algorithm.
    A new assignment should not be created.
    The assignment passed in should have its domains updated with inferences.
    In the case that a recursive call returns failure or a variable assignment is incorrect,
    the inferences made along the way should be reversed.
    See maintainArcConsistency and forwardChecking for the format of inferences.

    Examples of the functions to be passed in:
    orderValuesMethod: orderValues, leastConstrainingValuesHeuristic
    selectVariableMethod: chooseFirstVariable, minimumRemainingValuesHeuristic
    inferenceMethod: noInferences, maintainArcConsistency, forwardChecking

    Args:
        assignment (Assignment): a partial assignment to expand upon
        csp (ConstraintSatisfactionProblem): the problem definition
        orderValuesMethod (function<assignment, csp, variable> returns list<value>):
            a function to decide the next value to try
        selectVariableMethod (function<assignment, csp> returns variable):
            a function to decide which variable to assign next
        inferenceMethod (function<assignment, csp, variable, value> returns set<variable, value>):
            a function to specify what type of inferences to use
    Returns:
        Assignment
        A completed and consistent assignment. None if no solution exists.
    """
    # TODO: Question 1
    #print("S1")
    if assignment.isComplete(): return assignment
    var = selectVariableMethod(assignment, csp)
    values = orderValuesMethod(assignment, csp, var)
    #print("S2")
    for value in values:
        #print("S3")
        if consistent(assignment, csp, var, value):
            
            #print("S4")
            inferences = inferenceMethod(assignment, csp, var, value)
            #print("S5")
            if inferences is not None:
                assignment.assignedValues[var] = value
                result = recursiveBacktracking(assignment, csp, orderValuesMethod, selectVariableMethod, inferenceMethod)
                if result is not None: return result
                assignment.assignedValues[var] = None
                for inference in inferences:
                    assignment.varDomains[inference[0]].add(inference[1])
    return None



def eliminateUnaryConstraints(assignment, csp):
    """
    Uses unary constraints to eleminate values from an assignment.

    Args:
        assignment (Assignment): a partial assignment to expand upon
        csp (ConstraintSatisfactionProblem): the problem definition
    Returns:
        Assignment
        An assignment with domains restricted by unary constraints. None if no solution exists.
    """
    domains = assignment.varDomains
    for var in domains:
        for constraint in (c for c in csp.unaryConstraints if c.affects(var)):
            for value in (v for v in list(domains[var]) if not constraint.isSatisfied(v)):
                domains[var].remove(value)
                # Failure due to invalid assignment
                if len(domains[var]) == 0:
                    return None
    return assignment


def chooseFirstVariable(assignment, csp):
    """
    Trivial method for choosing the next variable to assign.
    Uses no heuristics.
    """
    for var in csp.varDomains:
        if not assignment.isAssigned(var):
            return var


# = = = = = = = QUESTION 2  = = = = = = = #


def minimumRemainingValuesHeuristic(assignment, csp):
    """
    Selects the next variable to try to give a value to in an assignment.
    Uses minimum remaining values heuristic to pick a variable. Use degree heuristic for breaking ties.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
    Returns:
        the next variable to assign
    """
    nextVar = None
    domains = assignment.varDomains

    # TODO: Question 2
    num_values = 10e9
    for var in domains:
        if len(domains[var]) != 0 and assignment.isAssigned(var) is not True:
            if(len(domains[var]) < num_values):
                num_values = len(domains[var])
                nextVar = var
    return nextVar
    


def orderValues(assignment, csp, var):
    """
    Trivial method for ordering values to assign.
    Uses no heuristics.
    """
    return list(assignment.varDomains[var])


# = = = = = = = QUESTION 3  = = = = = = = #


def leastConstrainingValuesHeuristic(assignment, csp, var):
    """
    Creates an ordered list of the remaining values left for a given variable.
    Values should be attempted in the order returned.
    The least constraining value should be at the front of the list.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
        var (string): the variable to be assigned the values
    Returns:
        list<values>
        a list of the possible values ordered by the least constraining value heuristic
    """
    # TODO: Question 3
    domains = assignment.varDomains
    values = list(domains[var])
    constraints = []
    for constraint in csp.binaryConstraints:
        if constraint.affects(var): constraints = constraints + [constraint]
    num_value = len(values)
    num_change = [0 for i in range(num_value)]
    for i in range(num_value):
        value = values[i]
        for constraint in constraints:
            other = constraint.otherVariable(var)
            other_values = domains[other]
            for other_value in other_values:
                if constraint.isSatisfied(value, other_value) is not True: num_change[i] += 1
    order = []
    for i in range(num_value):
        order += [(num_change[i],values[i])]
    order.sort()
    result = []
    for i in range(num_value):
        result += [(order[i][1])]
    return result


    


def noInferences(assignment, csp, var, value):
    """
    Trivial method for making no inferences.
    """
    return set([])


# = = = = = = = QUESTION 4  = = = = = = = #


def forwardChecking(assignment, csp, var, value):
    """
    Implements the forward checking algorithm.
    Each inference should take the form of (variable, value)
    where the value is being removed from the domain of variable.
    This format is important so that the inferences can be reversed
    if they result in a conflicting partial assignment.
    If the algorithm reveals an inconsistency,
    any inferences made should be reversed before ending the function.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
        var (string): the variable that has just been assigned a value
        value (string): the value that has just been assigned
    Returns:
        set< tuple<variable, value> >
        the inferences made in this call or None if inconsistent assignment
    """
    inferences = set([])

    # TODO: Question 4
    #print("forward")
    domains = assignment.varDomains
    constraints = []
    for constraint in csp.binaryConstraints:
        if constraint.affects(var): constraints = constraints + [constraint]
    for constraint in constraints:
        other = constraint.otherVariable(var)
        other_values = domains[other]
        for other_value in list(other_values):
            if constraint.isSatisfied(value, other_value) is not True:
                assignment.varDomains[other].remove(other_value)
                inferences.add((other, other_value))
                if len(assignment.varDomains[other]) == 0: return None
    return inferences


# = = = = = = = QUESTION 5  = = = = = = = #


def revise(assignment, csp, var1, var2, constraint):
    """
    Helper function to maintainArcConsistency and AC3.
    Remove values from var2 domain if constraint cannot be satisfied.
    Each inference should take the form of (variable, value)
    where the value is being removed from the domain of variable.
    This format is important so that the inferences can be reversed
    if they result in a conflicting partial assignment.
    If the algorithm reveals an inconsistency,
    any inferences made should be reversed before ending the function.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
        var1 (string): the variable with consistent values
        var2 (string): the variable that should have inconsistent values removed
        constraint (BinaryConstraint): the constraint connecting var1 and var2
    Returns:
        set<tuple<variable, value>>
        the inferences made in this call or None if inconsistent assignment
    """
    inferences = set([])

    # TODO: Question 5
    values1 = assignment.varDomains[var1]
    values2 = assignment.varDomains[var2]
    for value2 in list(values2):
        is_meet = False
        for value1 in values1:
            if constraint.isSatisfied(value1, value2): is_meet = True
        if is_meet is False:
            inferences.add((var2,value2))
            assignment.varDomains[var2].remove(value2) 

    return inferences

class Queue:
    "A container with a first-in-first-out (FIFO) queuing policy."

    def __init__(self):
        self.list = []

    def push(self, item):
        "Enqueue the 'item' into the queue"
        self.list.insert(0, item)

    def pop(self):
        """
        Dequeue the earliest enqueued item still in the queue. This
        operation removes the item from the queue.
        """
        return self.list.pop()

    def isEmpty(self):
        "Returns true if the queue is empty"
        return len(self.list) == 0


def maintainArcConsistency(assignment, csp, var, value):
    """
    Implements the maintaining arc consistency algorithm.
    Inferences take the form of (variable, value)
    where the value is being removed from the domain of variable.
    This format is important so that the inferences can be reversed
    if they result in a conflicting partial assignment.
    If the algorithm reveals an inconsistency,
    and inferences made should be reversed before ending the function.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
        var (string): the variable that has just been assigned a value
        value (string): the value that has just been assigned
    Returns:
        set<<variable, value>>
        the inferences made in this call or None if inconsistent assignment
    """
    inferences = set([])
    domains = assignment.varDomains

    # TODO: Question 5
    #  Hint: implement revise first and use it as a helper function"""
    queue = Queue()
    constraints = [constraint for constraint in csp.binaryConstraints if constraint.affects(var)]
    for constraint in constraints:
        other = constraint.otherVariable(var)
        queue.push((var, other, constraint))
    while queue.isEmpty() is not True:
        (xi, xj, constraint) = queue.pop()
        inf = revise(assignment, csp, xi, xj, constraint)
        if len(inf) != 0:
            if len(domains[xj])==0: return None
            constraints = [constraint for constraint in csp.binaryConstraints if constraint.affects(xj)]
            for constraint in constraints:
                xk = constraint.otherVariable(xj)
                queue.push((xj, xk, constraint))
            for i in inf:
                inferences.add(i)
    return inferences


# = = = = = = = QUESTION 6  = = = = = = = #


def AC3(assignment, csp):
    """
    AC3 algorithm for constraint propagation.
    Used as a pre-processing step to reduce the problem
    before running recursive backtracking.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
    Returns:
        Assignment
        the updated assignment after inferences are made or None if an inconsistent assignment
    """
    inferences = set([])

    # TODO: Question 6
    #  Hint: implement revise first and use it as a helper function"""
    queue = Queue()
    variables = [var for var in assignment.varDomains]
    for var in variables:
        constraints = [constraint for constraint in csp.binaryConstraints if constraint.affects(var)]
        for constraint in constraints:
            other = constraint.otherVariable(var)
            queue.push((var,other,constraint))

    while queue.isEmpty() is not True:
        (xi, xj, constraint) = queue.pop()
        inf = revise(assignment, csp, xi, xj, constraint)
        if len(inf) != 0:
            if len(assignment.varDomains[xj]) == 0: return None
            constraints = [constraint for constraint in csp.binaryConstraints if constraint.affects(xj)]
            for constraint in constraints:
                xk = constraint.otherVariable(xj)
                queue.push((xj, xk, constraint))
    return assignment
    


def solve(csp, orderValuesMethod=leastConstrainingValuesHeuristic,
          selectVariableMethod=minimumRemainingValuesHeuristic,
          inferenceMethod=forwardChecking, useAC3=True):
    """
    Solves a binary constraint satisfaction problem.

    Args:
        csp (ConstraintSatisfactionProblem): a CSP to be solved
        orderValuesMethod (function): a function to decide the next value to try
        selectVariableMethod (function): a function to decide which variable to assign next
        inferenceMethod (function): a function to specify what type of inferences to use
        useAC3 (boolean): specifies whether to use the AC3 pre-processing step or not
    Returns:
        dictionary<string, value>
        A map from variables to their assigned values. None if no solution exists.
    """
    assignment = Assignment(csp)

    assignment = eliminateUnaryConstraints(assignment, csp)
    if assignment is None:
        return assignment

    if useAC3:
        assignment = AC3(assignment, csp)
        if assignment is None:
            return assignment

    assignment = recursiveBacktracking(assignment, csp, orderValuesMethod, selectVariableMethod, inferenceMethod)
    if assignment is None:
        return assignment

    return assignment.extractSolution()
