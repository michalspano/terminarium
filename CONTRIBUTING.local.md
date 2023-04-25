# Terminarium - Contribution Standards

The purpose of this document is **to establish a contribution standard** for _contributors_ of the `Terminarium` project as well as ensuring that individual _contributions_ are well-formed and fulfill relevant criteria. 


## Table of Contents

- [Contribution Guidelines](#contribution-guidelines)
  - [Requirements](#requirements)
  - [Labels](#labels)
  - [Issues](#issues)
    - [Creating New Issues](#creating-new-issues)
    - [Naming Convention](#naming-convention)
    - [Issue Templates](#issue-templates)
  - [Milestones](#milestones)
  - [Feature Branches](#feature-branches)
  - [Commits](#commits)
  - [Merge Requests](#merge-requests)
- [Help Section (WIP)](#help-section)


# Contribution Guidelines 

To ensure correctness and traceability in project contributions, **all contributors** are expected to have **read and understood** the content in this section:


## Requirements

---

The system requirements are written either in the SRS-format or as user epics, which are then broken down into smaller user stories - each relating to one [issue](#issues). 

> TODO: add link to the wiki requirements page when it has been created.


## Labels

---

Labels are used to organise [issues](#issues) and [milestones](#milestones) - **appropriate labels must always be attached.** 

A list of labels and their full desciptions can be found [here](https://git.chalmers.se/courses/dit113/2023/group-15/terminarium/-/labels).


## Issues

---

Issues are used to describe tasks, track (their) progress, communicate around them, and most importantly: *traceability*.

Issues **must have an acceptance criteria**, that is, a set of criteria to be fulfilled in order for the issue to be deemed resolved. 

Every issue must have its own [_feature_ branch](#feature-branches), named accordingly.

### Creating New Issues

Adding a new issue requires an **appropriate title**, a **description** (for which there are [templates](#issue-templates)), an **_assignee_** - responsible for the implementation - and a **due date**. 

Issues must also have suitable [labels](#labels) attached and, optionally, be part of a [milestone](#milestones), such as for example `Sprint 1`. 

### Naming Convention

Write **issue titles** using the [imperative mood](https://en.wikipedia.org/wiki/Imperative_mood), such that it forms a command or request.

### Issue Templates

<!-- should this instead request that contributors ALWAYS use a template? --> 
When creating and writing **new issues** there is an option to select a template that specifies a pre-determined structured format. 

The `Terminarium` repository (currently) contains the following template(s):

> In-detail descriptions of each template can be found (by selecting them) during creation of a new issue.

- **Requirement** - defines the structure for a requirement type issue; applicable to a majority of project contributions. 
  <!-- is the following necessary? -->
  Determines the following structure:
  - Issue Description
  - Acceptance Criteria
  - Related Issues

> TODO: add more templates (?)


## Milestones

---

Milestones consist of a group of [requirements](#requirements) that together make up a particular milestone. For a milestone to have been achieved the associated [issues](#issues) must first be **closed** (completed or otherwise moved out of scope).

Each project _sprint_ has its own sprint milestone (and accompanying [label](#labels)).


## Feature Branches

---

Branches are used when implementing new contributions into the project. Any additions or changes related to the implementation of a certain [issue](#issues) must first be made using the correlating branch, and later on *merged* with the `main branch` via a [merge-request](#merge-requests). 

Branch names must also include the related **issue number** as prefix, for example: 
> "**#21**-add-contributing-md"


## Commits

---

All commits must contain an appropriate title and desciption.

The first part of the title message **must always include the related [issue number](#issues)**.


## Merge requests

---

Once a feature has been completed (after testing) a merge-request is to be created, asking to merge the [feature branch](#feature-branches) into main. 

For the _Terminarium_ project - merge-requests **must always involve a secondary person to review and validate** the implementation before approving the request.



# Help Section
<!-- better name for this section? -->
> TODO: implement this section 

## Contribution Tutorials / Checklists ???

Step-by-step guide(s); how to create merge-request, all the way from local > remote
<!-- include details like labels etc. -->

## TODO: Git tips, tricks & useful commands
- add useful commands
- add info from canvas slides (both MP courses)

