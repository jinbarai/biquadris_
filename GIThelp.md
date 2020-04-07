
## Git branches:
Usually add branches for each feature
1. To create a new branch
``` git branch <branchName> ```

2. To switch to the branch
``` git checkout <branchname> ```

3. This should show the branch on which you are on
``` git status ```
  
   (To see a list of branches use ``` git branch -a ```)

## Git Usage:
  (Note: Please make sure you work on your branch and then follow the steps below) 

1. Puts the file into staging; the '.' adds all files, if you wanted to stage only certain files just do git add <filename>
``` git add . ```
  
2. To commit all the files that you have staged above
``` git commit -m "<Include commit message here, make sure it is meaningful>" ```

3. Follow this step if it's your **first commit with the branch**. What we're doing here is trying to do here in simple words establishing some sort of connection between the branch and the master branch. (More on: https://devconnected.com/how-to-set-upstream-branch-on-git/) 
``` git push --set-upstream origin <branchName> ```

4. If you've used the above command
  ``` git push origin ``` should do it for you this time. No need to set an upstream again! 

## Pull Requests:
1. As soon as you're done with the above, once you reload the git page (https://github.com/kimiashaban/cs246a5) you'll see your branch name on top (for some reason I'm not able to attach ss, I'll look into that later lol) along with an option that says "Compare and Pull Requests". 

2. Click on compare and pull requests 
3. Add reviewer
4. Click on Create Pull Request
5. The reviewer will approve the changes and you can then click on merge (this will merge the code into the master) and it's safe to delete your branch now!! :D 

## Forgot about Pull, shall do that later 

