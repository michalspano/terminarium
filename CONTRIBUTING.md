## Guidelines for creating issues

- When creating an issue that corresponds to a **feature request**, it is important to adhere to the provided **issue template**.
  - The template should include a **user story** or a Software System Requirements (SSR) description. Alternatively, if more feasible, a textual natural language description can be used.
  - The author should also provide **acceptance criteria** that outline the specific requirements that must be met for the feature to be considered complete.
  - For bug fixes or documentation enhancements, a textual natural language description is sufficient to describe the issue.
- When creating an issue, the author of the issue should assign themselves as the **assignee**.
- Additionally, the appropriate **labels** should be added, such as *"enhancement"* for a new feature or *"bug"* for a bug in the code.
- Labels for **priority** (e.g. `priority:medium`)and **Sprint/Milestone** (e.g. `Sprint:2`) information should **always** be provided. 
  - The Sprint/Milestone label can be omitted for bug fixes or other similar issues.
- An appropriate **due date** should be added to the issue with respect to the milestone's deadline.
- Once an issue is created, the author can continuously **updates** the acceptance criteria based on the committed implementations to track what work remains to be done.

## Guidelines for writing commit messages

- To ensure traceability, commit messages must be written in the **imperative style** and should **include** the corresponding **issue** via the `#<n>` syntax.
- Additionally, it is highly recommended to provide a **description** for each commit. It should cover the **rationale** for the changes and the **approach** taken to implement them.
- In cases where **multiple individuals** work on a commit, the *"Co-authors: ..."* convention should be utilized to acknowledge their contribution.

## Guidelines for creating branches

- In adherence to the **feature-branch workflow**, a distinct branch should be created for every issue. It is significant to ensure that the branch is created from the corresponding issue. The **name** assigned to the branch should be **succinct**, while also bearing **resemblance** to the content of the issue.

## Guidelines for creating and/or handling merge requests

- A **merge request** must have an **assignee** (i.e., the author of the corresponding issue) and a **reviewer** (a different team member).
- The merge request shall:
  - retain the **labels** from the issue, including the *'needs-review'* label, upon creation;
  - retain the **milestone** from the issue.
- As a **reviewer**, the duties are to:
  - ensure that the code meets acceptable quality standards and fulfills the desired feature request,
  - provide **feedback** and/or **code reviews** to improve the feature if necessary,
  - *approve* the merge request if they believe it is suitable for the system's development.
- Once the merge request is approved, the *'needs-review'* label should be removed, and the *'status:ok'* label added.
- Only after these steps have been completed can the **assignee** *merge* the merge request.
  
## Guidelines for closing issues

- In the event that a particular feature is **deemed unfeasible** or outside of the project scope, it may be *closed* with the addition of the *'deprecated'* label. If necessary, the feature can be revisited and subsequently *reopened*.

## Checklist for team members

The following should be continuously checked during the development process; as a **team member**, you are expected to question yourself and your peers on the following:

1. Have you followed the issue template when creating a new issue that requests a new feature?
2. Have you provided acceptance criteria for the feature that you are working on?
3. Have you used the imperative style and included the issue number in the commit message to ensure traceability?
4. Have you created a separate branch for each issue and named the branch appropriately?
5. Have you assigned an assignee and reviewer for each merge request?
6. Have you retained the labels and milestone from the original issue in the merge request?
7. Have you thoroughly reviewed the code and added comments or suggestions for improvement as necessary?
8. Have you approved the merge request only if you believe that it is suitable for application to the development of the system, and similarly changed the labels accordingly?
9. Have you closed a feature as deprecated if it is no longer feasible or not part of the scope anymore?
10. Have you raised any incidents of misconduct to the PM of the project as necessary?

### Markdown style guide

- All team member are encouraged to adhere to the **standard Markdown syntax**. If necessary, the [Markdown Cheatsheet](https://docs.gitlab.com/ee/user/markdown.html) can be used as a reference.

### Reporting misconduct

- In case of any inappropriate behavior, it is the **duty** of team members to escalate the matter to the Project Manager (@spano) for further action.
