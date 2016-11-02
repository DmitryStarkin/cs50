import _thread as thread
import re
from string import punctuation

class Analyzer():
    """Implements sentiment analysis."""
       
    def loadDic (self, myId, filename, listName):
        try:
            for line in open(filename):
                    if (";" not in line) and line.strip():
                        line = line.replace("\n", "")
                        listName.append(line)
        except Exception: 
            self.accessLock.acquire()
            self.loading = False
            self.accessLock.release()
        finally:                
            self.exitmutexes[myId].acquire()
    
    def __init__(self, positives="positive-words.txt", negatives="negative-words.txt"):
        """Initialize Analyzer."""

        # TODO
        self.posword = []
        self.negword = []
        self.loading = True
        self.accessLock = thread.allocate_lock()
        self.regex = re.compile('[%s]' % re.escape(punctuation))
        self.exitmutexes = [thread.allocate_lock() for i in range(2)]
        
        thread.start_new_thread(self.loadDic, (0, positives, self.posword))
        thread.start_new_thread(self.loadDic, (1, negatives, self.negword))
        
        for mutex in self.exitmutexes:
            while not mutex.locked(): pass
        if not self.loading:
            raise IOError("cannot load dictionary")    

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # TODO
        score = 0.0
        words = []
        
        oneline = text.replace('\n', ' ')        
        lineWithoutPunctuation = self.regex.sub('', oneline)
        uncasedWords = lineWithoutPunctuation.split()
        
        for word in uncasedWords:
            words.append(word.strip().lower())
         
        for word in words:
            if (word in self.posword):
                score += 1
            elif (word in self.negword):
                score -= 1    
        return score
